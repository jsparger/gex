//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/data/DataModuleGroup.hh"
#include "gex/data/NamedData.hh"
#include "gex/util/make_unique.hh"
#include "gex/ua/RootTreeManager.hh"
#include "gex/data/RootDictionaryBuilder.hh"
#include "gex/ua/UserActionManager.hh"
#include "gex/ua/RunDataRegistration.hh"
#include "gex/util/Access.hh"
#include "gex/sd/SDGroup.hh"
#include "gex/create.hh"
#include "gex/ua/Callback.hh"
#include <iostream>

namespace gex {
namespace data {
	
DataModuleGroup* make_readout(sd::SDGroup* sdGroup, std::string branchName)
{
	auto dataGroup = gex::create<data::DataModuleGroup>(branchName);
	gex::create<ua::Callback>([dataGroup]{dataGroup->reset();}, std::set<ua::Cycle>{ua::Cycle::EVENT_BEGIN});
	sdGroup->inform(dataGroup);
	return dataGroup;
}

DataModuleGroup::
DataModuleGroup(const std::string& n)
	: //DataModule(name),
		name(n), currentKey(""), gotKey(false)
{
	// do nothing else
}

void
DataModuleGroup::
reset()
{
	gotKey = false;
	currentKey = "";
	collection.reset();
}

DataModuleGroup&
DataModuleGroup::
add(std::unique_ptr<DataModule> mod)
{
	moduleVec.push_back(mod.get());
	ownedModuleVec.push_back(std::move(mod));
	return *this;
}

DataModuleGroup&
DataModuleGroup::
add(DataModule* mod)
{
	moduleVec.push_back(mod);
	return *this;
}

void
DataModuleGroup::
registerWith(ua::RootTreeManager* rtm, std::string treeName)
{	
	// register the type
	auto* rDict = data::RootDictionaryBuilder::GetRootDictionaryBuilder();
	rDict->registerData(&collection);
	
	for (DataModule* mod : moduleVec)
	{
		auto data = mod->createData();
		rDict->registerData(data.get());
	}
	
	// set up data registration.
	auto* uam = ua::UserActionManager::GetUserActionManager();
	auto dataReg = std::make_unique<ua::RunDataRegistration<DataType>>(rtm, treeName, this->name, &collection);
	uam->registerAction(std::move(dataReg));
	
	// set up fill condition
	rtm->setFillCondition(treeName,&gotKey);	
}

void
DataModuleGroup::
setKey(const std::string& key)
{
	//static int numHits = 0;
	gotKey = true;
	if (key != currentKey)
	{
		currentKey = key;
		bool isNew = false;
		if (collection.keyIndexTable.find(key) == collection.keyIndexTable.end())
		{
			//++numHits;
			//std::cout << numHits << "\n";
			isNew = true;
			collection.vec.push_back(data::NamedData());
			collection.keyIndexTable.emplace(key,collection.vec.size()-1);
		}
		
		distributeData(collection.vec[collection.keyIndexTable[key]], isNew);
	}
}

void
DataModuleGroup::
distributeData(NamedData& namedData, bool isNew)
{
	auto access = util::get_access(namedData);
	for (DataModule* mod : moduleVec)
	{
		if (isNew)
		{
			// auto data = util::value_ptr<IData>(mod->createData().release()); // commented out on 4/15/2014
			// namedData.typeMap.emplace(mod->getModuleName(), data->getDataType());
// 			namedData.dataMap.emplace(mod->getModuleName(), std::move(data));
			// namedData.add(mod->getModuleName(), std::move(data)); // commented out on 4/15/2014
			
			// TODO: TROUBLE! this seems crappier. Memory will leak if insert fails.
			access.insert(mod->getModuleName(),mod->createData().release());
		}
		
		//mod->setData(namedData.dataMap[mod->getModuleName()].get());
		// mod->setData(namedData.store[mod->getModuleName()].get());// commented out on 4/15/2014
		mod->setData(access.get<data::IData>(mod->getModuleName()));
	}
}

	
} // namespace data 	
} // namespace gex 
