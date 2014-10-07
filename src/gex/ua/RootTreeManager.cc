//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/ua/RootTreeManager.hh"
#include "gex/ua/UserActionManager.hh"
#include <sstream>
#include "G4Threading.hh"
#include <iostream>
#include "TMemFile.h"
#include "gex/util/RootLock.hh"
// #include "gex/util/make_unique.hh"
#include "gex/data/RootDictionaryBuilder.hh"

namespace gex {
namespace ua {

thread_local std::map<std::string,std::unique_ptr<RootTreeManager>> RootTreeManager::instanceMap; 

RootTreeManager*
RootTreeManager::
GetRootTreeManager(const std::string& name)
{
	if (instanceMap.find(name) == instanceMap.end())
	{
		std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
		instanceMap[name] = std::move(std::unique_ptr<RootTreeManager>(new RootTreeManager(name)));
	}

	return instanceMap[name].get();
}

RootTreeManager::
RootTreeManager(const std::string& n)
	: file(nullptr), name(n), description(""), runNumber(0), autoFill(true), firstTime(true)
{
	// do nothing else
}

void
RootTreeManager::
registerWith(UserActionManager* uam)
{
	uam->addEventAction(this);
	uam->addRunAction(this);
}

void
RootTreeManager::
setFillCondition(const std::string& treeName, bool* fillCondition)
{
	auto it = fillConditionMap.find(treeName);
	if (it != fillConditionMap.end())
	{
		it->second = fillCondition;
	}
	else
	{
		treeMap.emplace(treeName, std::make_unique<TTree>(treeName.c_str(), description.c_str()));
		fillConditionMap.emplace(treeName,fillCondition);
	}
}

void
RootTreeManager::
BeginOfRunAction(const G4Run*)
{
	if (firstTime)
	{
		data::RootDictionaryBuilder::GetRootDictionaryBuilder()->buildDictionary();
		firstTime = false;
	}
		
	if (G4Threading::IsWorkerThread())
	{
		// TODO: need to hide these types of root operations requiring a lock in a class
		std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
		
		// It seems that ROOT I/O is NEVER threadsafe.
		// The internet suggests it should be if each thread has its own file and trees,
		// but this does not seem to be true.
		
		// create a TFile for the run
		std::stringstream ss;
		ss << name << "_run" <<runNumber << "_tr" << G4Threading::G4GetThreadId() << ".root";
		file = std::make_unique<TFile>(ss.str().c_str(), "RECREATE", description.c_str());
		
		// create new trees for the new file. 
		for (auto& pair : treeMap)
		{
			pair.second = std::make_unique<TTree>(pair.first.c_str(), description.c_str());
		}	
	}
}

void
RootTreeManager::
EndOfRunAction(const G4Run*)
{
	if (G4Threading::IsWorkerThread())
	{
		// TODO: need to hide these types of root operations requiring a lock in a class
		std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
				
		// if worker thread, write and delete the TTrees
		file->cd();
		for (auto& pair : treeMap)
		{
			pair.second->Write();
			// apparently the TFile will delete the trees when it is deleted, 
			// so call release instead of reset. Should maybe change this to raw pointer.
			pair.second.release(); 
		}
				
		// write and delete the TFile
		file->Write();
		file->Close();
		file.reset(nullptr);
		
		// increment run number
		++runNumber;		
	}	
}

void
RootTreeManager::
processFile()
{
	// do nothing
}

void
RootTreeManager::
BeginOfEventAction(const G4Event*)
{
	// do nothing
}

void
RootTreeManager::
EndOfEventAction(const G4Event*)
{
	// it is apparently NEVER okay to call TTree::Fill in parallel, despite what forums suggest.
	// sometimes this seems to work without a lock. 
	// Sometimes it fails miserably. Possibly works without lock when TApplication is created at
	// beginning of main. I don't understand to be honest.
	std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
	
	for (auto& pair : fillConditionMap)
	{
		if (*pair.second)
		{
			treeMap[pair.first]->Fill();
		}
	}
}
	
} // namespace ua
} // namespace gex
