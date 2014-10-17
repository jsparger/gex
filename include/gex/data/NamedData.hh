//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_NAMED_DATA_HH
#define GEX_DATA_NAMED_DATA_HH

#include "gex/data/IData.hh"
#include <map>
#include <string>
#include "TString.h"
#include "gex/util/value_ptr.hh"
//#include "gex/util/type_erasure.hh"
//#include "gex/util/any.hh"

namespace gex {
namespace data {

/// \class NamedData
/// \brief A type erased map of data suitable for storage in a Root TTree.
///
/// NamedData is an IData type that stores any IData type along with a name string. It uses gex::util::value_ptr to allow for the correct behavior when stored using a ROOT TTree. Values in the NamedData may be manipulated using a gex::util::Access which can be gotten via the gex::util::get_access() function. 
	
struct NamedData : public IData
{
	
	NamedData()
	{
		// do nothing else
	}
	
	NamedData(NamedData&& other)
		: store(std::move(other.store))
	{
		// do nothing else
	}
	
	NamedData(const NamedData& other)
		: store(other.store)
	{
		// do nothing else
	}
	
	NamedData& operator=(const gex::data::NamedData& other)
	{
		store = other.store;
		return *this;
	}
	
	virtual ~NamedData() {;}
	
	virtual void reset() override
	{
		store.clear();
	}
	
	virtual IData* clone()
	{
		return new NamedData(*this);
	}
	
	virtual std::string getDataType() override
	{
		return "gex::data::NamedData";
	}
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::util::value_ptr<gex::data::IData>");
		types.push_back("pair<std::string,gex::util::value_ptr<gex::data::IData>>");
		types.push_back("std::map<std::string,gex::util::value_ptr<gex::data::IData>>");
		types.push_back("pair<std::string,gex::data::IData>");
		types.push_back("std::map<std::string,gex::data::IData>");
		types.push_back("pair<std::string,std::string>");
		types.push_back("std::map<std::string,std::string>");
		types.push_back("gex::data::NamedData");
		return types;
	}
	
	static std::vector<std::string> GetDictionaryHeaders()
	{
		std::vector<std::string> headers = IData::GetDictionaryHeaders();
		//headers.push_back("gex/util/type_erasure.hh");
		headers.push_back("gex/util/value_ptr.hh");
		headers.push_back("map");
		headers.push_back(__FILE__);
		return headers;
	}
	
	virtual std::vector<std::string> getDictionaryTypes()
	{
		return GetDictionaryTypes();
	}
	
	virtual std::vector<std::string> getDictionaryHeaders()
	{
		return GetDictionaryHeaders();
	}
	
	virtual bool add(const std::string& name, gex::util::value_ptr<IData> data)
	{
		const auto& dataMapPair = store.emplace(name, std::move(data));
		return dataMapPair.second;
	}
	
	typedef std::map<std::string, gex::util::value_ptr<IData>> container_type;
	std::map<std::string, gex::util::value_ptr<IData>> store;
	

};
	
} // namespace data 	
} // namespace gex 

#endif
