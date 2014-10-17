//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/GenericSource.hh"
#include "gex/pga/EnergyDistribution.hh"
#include "gex/pga/AngularDistribution.hh"
#include "gex/pga/SpatialDistribution.hh"
#include "gex/pga/ParticleDistribution.hh"

namespace gex {
namespace pga {
	
GenericSource::
GenericSource(EnergyDistribution* e, AngularDistribution* a, SpatialDistribution* pos, ParticleDistribution* p)
	:	energyDist(e), angularDist(a),
		spatialDist(pos), particleDist(p),
		gun(new G4ParticleGun())
{
	// do nothing else
}

void
GenericSource::
GeneratePrimaries(G4Event* theEvent)
{
	// set the properties of the primary
	gun->SetParticleDefinition(particleDist->getParticleType(theEvent));
	gun->SetParticleEnergy(energyDist->getEnergy(theEvent));
	gun->SetParticleMomentumDirection(angularDist->getDirection(theEvent));
	gun->SetParticlePosition(spatialDist->getPosition(1,theEvent));
	
	// generate the primary
	gun->GeneratePrimaryVertex(theEvent); 
}
	
} // namespace pga 
} // namespace gex 
