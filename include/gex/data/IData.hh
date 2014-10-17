//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_IDATA
#define GEX_DATA_IDATA 

#include <string>
#include <vector>

namespace gex {
namespace data {

/// \class IData
/// \brief Abstract base for data classes which use run-time ROOT dictionary compilation.
///
///
struct IData
{
	virtual ~IData() {;}
	virtual std::string getDataType() {return "gex::data:IData";}
	
	virtual void reset() {;}
	
	virtual IData* clone() { return new IData(); }
		
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types;
		types.push_back("gex::data::IData");
		return types;
	}
	
	static std::vector<std::string> GetDictionaryHeaders()
	{
		std::vector<std::string> headers;
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
};
	
} // namespace data 	
} // namespace gex 

#endif
