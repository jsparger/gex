//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/MonoEnergyDist.hh"

namespace gex {
namespace pga {

MonoEnergyDist::
MonoEnergyDist(double e)
	: energy(e)
{
	// do nothing else
}

double
MonoEnergyDist::
getEnergy(G4Event*)
{
	return energy;
}
	
} // namespace pga 	
} // namespace gex 
