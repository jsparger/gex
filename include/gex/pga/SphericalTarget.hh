//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_SPHERICAL_TARGET_HH
#define GEX_PGA_SPHERICAL_TARGET_HH

#include "gex/pga/GenericSource.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "Math/Random.h"

namespace gex {
namespace pga {

/// \class SphericalTarget
/// \brief A GenericSource which only shoots primaries expected to hit a target.
///
/// SphericalTarget skips the simulation of particles which are not expected to hit a specific target. This can help the user avoid expensive computations for particles unlikely to affect the results of the simulation, such as those which will never hit the detector. To use this class, the user must define the location and radius of a spherical target zone. Only particles whose initial momentum directions intersect this target will be simulated. SphericalTarget will, however, advance each of the distributions by the correct number of samples to allow for any time/sequence dependencies to play out correctly.
class SphericalTarget : public GenericSource
{
public:
	
	/// Constructor. Takes a position and radius for the spherical target zone and the standard distributions required by GenericSource. Additionally, the \p recomputeDistance, which defaults to 1 cm, determines how much the location of the source can change without triggering a recomputation of the target cone. A smaller recompute distance will be more accurate and ensure particles are always emitted in the right direction, but a larger recompute distance will avoid expensive recalculations.
	SphericalTarget(G4ThreeVector targetPos, double targetRadius,
					EnergyDistribution* eDist, SpatialDistribution* pDist, 
					ParticleDistribution* parDist, double recomputeDistance = 1*cm);
					
	virtual ~SphericalTarget() {;}
	virtual void GeneratePrimaries(G4Event* e) override;
	
protected:
	virtual void fillPrimaryVertexData(G4Event* e);
	
	G4ThreeVector pos, toCenter, targetPos, up, rotAxis, lastRecomputePos;
	double phi, targetRadius, recomputeDistance, acceptanceProb;
	bool firstTime;
	ROOT::Math::RandomMT random;
};
	
} // namespace pga 	
} // namespace gex 

#endif
