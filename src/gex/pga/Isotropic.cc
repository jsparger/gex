//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/Isotropic.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"

namespace gex {
namespace pga {

G4ThreeVector
Isotropic::
getDirection(G4Event*)
{
	// sample uniformly on sphere. Taken from:
	// http://math.stackexchange.com/questions/44689/how-to-find-a-random-axis-or-unit-vector-in-3d
	
	double theta = G4UniformRand()*2*pi; // sample theta uniformly from [0,2pi)
	double z = G4UniformRand()*2-1; // sample z uniformly from [-1,1]
	double c = std::sqrt(1-z*z);
	double x = c*std::cos(theta);
	double y = c*std::sin(theta);
	
	// return the direction.
	return G4ThreeVector(x,y,z).unit();
}

} // namespace pga 	
} // namespace gex 
