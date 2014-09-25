//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_PRIMARY_VERTEX_DATA_HH
#define GEX_DATA_PRIMARY_VERTEX_DATA_HH

#include "gex/data/IData.hh"

namespace gex {
namespace data {
	
/// \class PrimaryVertexData
/// \brief Holds information about particle generated by a PrimaryGeneratorAction
///
/// PrimaryVertexData holds information about the primaries generated by a PrimaryGeneratorAction. It contains the momentum direction, position of emission, energy, momentum, global time of emission, particle type, and number of particles.
struct PrimaryVertexData : public IData
{
	PrimaryVertexData() : isSet(false) {;}
	virtual ~PrimaryVertexData() {;}
	virtual void reset()
	{
		isSet = false;
	}

	virtual IData* clone()
	{
		return new PrimaryVertexData(*this);
	}

	virtual std::string getDataType()
	{
		return "gex::data::PrimaryVertexData";
	}

	static std::vector<std::string> GetDictionaryTypes()
	{
		std::vector<std::string> types = IData::GetDictionaryTypes();
		types.push_back("gex::data::PrimaryVertexData");
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
	
	void setMomentumDirection(double x, double y, double z)
	{
		momentumDir[0] = x;
		momentumDir[1] = y;
		momentumDir[2] = z;
	}
	
	void setPosition(double x, double y, double z)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}

	double momentumDir[3];
	double position[3];
	double energy, momentum, globalTime;
	unsigned int particleType, numParticles;
	bool isSet;
};
	
} // namespace data 
} // namespace gex 

#endif