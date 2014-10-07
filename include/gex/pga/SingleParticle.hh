//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_SINGLE_PARTICLE_HH
#define GEX_PGA_SINGLE_PARTICLE_HH

#include "gex/pga/ParticleDistribution.hh"

namespace gex {
namespace pga {

/// \class SingleParticle
/// \brief A single particle distribution
///
/// SingleParticle is a particle distribution which always returns the same particle type. Choose this particle distribution if your source only emits one type of particle.
class SingleParticle : public ParticleDistribution
{
public:
	/// Constructor. Takes a G4ParticleDefinition pointer. This is the only type of particle this distribution will produce.
	SingleParticle(G4ParticleDefinition* particle);
	virtual ~SingleParticle() {;}
	virtual G4ParticleDefinition* getParticleType(G4Event* event = nullptr) override;

protected:
	G4ParticleDefinition* particle;
};
	
} // namespace pga 
} // namespace gex 

#endif
