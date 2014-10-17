//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UA_ROOT_TREE_MANAGER_HH
#define GEX_UA_ROOT_TREE_MANAGER_HH

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "gex/ua/UserAction.hh"
#include <memory>
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <mutex>
#include "gex/util/make_unique.hh"
#include "gex/util/RootLock.hh"


namespace gex {
namespace ua {

/// \class RootTreeManager
/// \brief A class which manages creation of and interaction with ROOT TTrees. 
/// 
/// The RootTreeManager manages the creation of Root TFiles, TTrees and branches therein. It also takes care of filling branches at the end of an Event. Additionally, it triggers the building and runtime linkage of ROOT dictionaries.
class RootTreeManager : public G4UserEventAction, public G4UserRunAction, public UserAction
{
public:
	/// A static function to get the thread local RootTreeManager which manages the TFiles given by the base name string \p name. The RootTreeManager will append the run number and thread number to this base name when creating TFiles.
	static RootTreeManager* GetRootTreeManager(const std::string& name);
	
	/// Registers data to be saved in a TTree. A branch with name \p dataName will be created in the tree given by \p treeName using the data location \p data. If the string \p treeName does not correspond to an existing tree, the tree will be created. 
	template <typename T>
	void registerData(std::string treeName, std::string dataName, T* data)
	{			
		std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
		file->cd();
		if (treeMap.find(treeName) == treeMap.end())
		{
			treeMap.emplace(treeName, std::make_unique<TTree>(treeName.c_str(), description.c_str()));
			fillConditionMap.emplace(treeName, &autoFill);
		}
		
		treeMap[treeName]->Branch(dataName.c_str(), data);
	}
	
	/// Sets a fill condition for the tree given by \p treeName. The value of the boolean pointed to by \p fillCondition will be evaluated before each fill, and the fill will only proceed if fillCondition is true.
	virtual void setFillCondition(const std::string& treeName, bool* fillCondition);
	virtual void processFile();
	
	virtual void BeginOfRunAction(const G4Run*) override;
	virtual void EndOfRunAction(const G4Run*) override;
	virtual void BeginOfEventAction(const G4Event* event) override;
	virtual void EndOfEventAction(const G4Event* event) override;
	virtual void registerWith(UserActionManager* uam) override;
	
protected:
	RootTreeManager(const std::string&);
	virtual ~RootTreeManager() {;}
	
	std::unique_ptr<TFile> file;
	std::map<std::string, std::unique_ptr<TTree>> treeMap;
	std::map<std::string,bool*> fillConditionMap;
	const std::string name;
	const std::string description;
	unsigned int runNumber;
	bool autoFill;
	bool firstTime;
	thread_local static std::map<std::string, std::unique_ptr<RootTreeManager>> instanceMap;
	friend std::unique_ptr<RootTreeManager>::deleter_type;
};

} // namespace ua
} // namespace gex

#endif
