//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_ENERGY_DATA_HH
#define GEX_DATA_ENERGY_DATA_HH

#include "gex/data/IData.hh"

namespace gex {
namespace data {

/// \class EnergyData
/// \brief Holds information about energy
///
///
struct EnergyData : public IData
{
	EnergyData(double energy = 0.0, bool isSet = false)
		: energy(energy), isSet(isSet)
	{
		// do nothing else
	}
	virtual ~EnergyData() {;}
	virtual void reset()
	{
		energy = 0;
		isSet = false;
	}
	
	virtual IData* clone()
	{
		return new EnergyData(*this);
	}
	
	virtual std::string getDataType()
	{
		return "gex::data::EnergyData";
	}
	
	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::data::EnergyData");
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
	
	double energy;
	bool isSet;
};
	
} // namespace data 	
} // namespace gex 

#endif
