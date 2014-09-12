//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_DETECTOR_DATA_HH
#define GEX_DATA_DETECTOR_DATA_HH

#include "gex/data/IData.hh"

namespace gex {
namespace data {

/// \class DetectorData
/// \brief Holds information about a detector volume
///
///
struct DetectorData : public IData
{
	DetectorData(std::string tName = "", int tCopyNumber = -1)
		: name(tName), copyNumber(tCopyNumber), isSet(false)
	{
		// do nothing else
	}
	virtual ~DetectorData() {;}
	virtual void reset()
	{
		isSet = false;
	}
	
	virtual IData* clone()
	{
		return new DetectorData(*this);
	}
	
	virtual std::string getDataType()
	{
		return "gex::data::DetectorData";
	}
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::data::DetectorData");
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
	
	std::string name;
	int copyNumber;
	bool isSet;
};
	
} // namespace data 	
} // namespace gex 

#endif
