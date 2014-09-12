//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_DATA_MODULE_GROUP_HH
#define GEX_DATA_DATA_MODULE_GROUP_HH

#include "gex/data/DataModule.hh"
#include "gex/data/NamedDataCollection.hh"
#include "gex/data/IDataOutputter.hh"
#include <memory>
#include <vector>

namespace gex {
namespace data {

/// \class DataModuleGroup
/// \brief Handles the registration, storage, and management of data from DataModules.
///
/// DataModuleGroup handles the registration, storage, and management of data from DataModules. The DataModuleGroup will make sure the dictionaries for all data types required by the group are built. It will also handle swapping data in and out of DataModules so that data is unique to a Volume (in conjunction with an SDGroup.) This coupling between DataModuleGroup, SDGroup, RootTreeManager, and RootDictionaryBuilder is more tight than it should be. Future development will break these couplings and make DataModuleGroup more general.
class DataModuleGroup : public IDataOutputter//, public DataModule
{
public:
	typedef NamedDataCollection DataType;
	
	/// Constructor. Requires a name for the group.
	DataModuleGroup(const std::string& name);
	virtual ~DataModuleGroup() {;}
	
	/// Add a DataModule to the group and transfer its ownership.
	virtual DataModuleGroup& add(std::unique_ptr<DataModule> mod);
	/// Add a DataModule to the group.
	virtual DataModuleGroup& add(DataModule* mod);
	/// A method which is called by SDGroup in a non-obvious way. This method will be refactored in a later version.
	virtual void setKey(const std::string& key);
	virtual void reset();
	
	// virtual std::unique_ptr<IData> createData() override;
// 	virtual void setData(IData* data) override;
	
	virtual void registerWith(ua::RootTreeManager* rtm, std::string treeName) override;
	
protected:
	virtual void distributeData(NamedData& nd, bool isNew);
	NamedDataCollection collection;
	std::string name;
	std::string currentKey;
	bool gotKey;
	std::vector<DataModule*> moduleVec;
	std::vector<std::unique_ptr<DataModule>> ownedModuleVec;
};
	
} // namespace data 
} // namespace gex 

#endif
