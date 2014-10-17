//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_PARTICLE_DISTRIBUTION_HH
#define GEX_PGA_PARTICLE_DISTRIBUTION_HH 

class G4ParticleDefinition;
class G4Event;

namespace gex {
namespace pga {

/// \class ParticleDistribution
/// \brief Abstract base class for particle type distributions.
class ParticleDistribution
{
public:
	virtual ~ParticleDistribution() {;}
	
	/// Sample a particle type.
	virtual G4ParticleDefinition* getParticleType(G4Event* event = nullptr) = 0;
};
	
} // namespace pga 
} // namespace gex 

#endif
