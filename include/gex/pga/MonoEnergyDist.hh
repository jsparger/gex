//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_MONO_ENERGY_DIST_HH
#define GEX_PGA_MONO_ENERGY_DIST_HH

#include "gex/pga/EnergyDistribution.hh"

namespace gex {
namespace pga {

/// \class MonoEnergyDist
/// \brief EnergyDistribution for monoenergetic source.
///
/// MonoEnergyDist is an EnergyDistribution which always returns a single energy.
class MonoEnergyDist : public EnergyDistribution
{
public:
	/// Constructor. Takes a single energy for the source.
	MonoEnergyDist(double energy);
	virtual ~MonoEnergyDist() {;}
	virtual double getEnergy(G4Event* event = nullptr) override;
protected:
	double energy;
};
	
} // namespace pga 
} // namespace gex 

#endif
