//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_POSITION_DATA
#define GEX_DATA_POSITION_DATA

#include "gex/data/IData.hh"

namespace gex {
namespace data {
	
/// \class PositionData
/// \brief Represents the a 3D position
///
/// 
struct PositionData : public IData
{
	PositionData(double tx = 0, double ty = 0, double tz = 0)
		: isValid(false), x(tx), y(ty), z(tz)
	{
		// do nothing else
	}
	virtual ~PositionData() {;}
	virtual void reset()
	{
		x = 0;
		y = 0; 
		z = 0;
		isValid = false;
	}
	
	virtual IData* clone()
	{
		return new PositionData(*this);
	}
	
	virtual std::string getDataType()
	{
		return "gex::data::PositionData";
	}
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::data::PositionData");
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
	
	bool isValid;
	double x, y, z;
	
};
	
} // namespace data 
} // namespace gex 

#endif
