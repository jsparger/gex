//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_TIME_DATA_HH
#define GEX_DATA_TIME_DATA_HH

#include "gex/data/IData.hh"

namespace gex {
namespace data {

/// \class TimeData
/// \brief Holds a value representing time.
///
///
struct TimeData : public IData
{
	TimeData()
		: isSet(false), time(0)
	{
		// do nothing else
	}
	virtual ~TimeData() {;}
	virtual void reset()
	{
		isSet = false;
		time = 0;
	}
	
	virtual IData* clone()
	{
		return new TimeData(*this);
	}
	
	virtual std::string getDataType()
	{
		return "gex::data::TimeData";
	}
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::data::TimeData");
		return types;
	}
	
	static std::vector<std::string> GetDictionaryHeaders()
	{
		std::vector<std::string> headers = IData::GetDictionaryHeaders();
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
	
	bool isSet;
	double time;
};
	
} // namespace data 	
} // namespace gex 

#endif
