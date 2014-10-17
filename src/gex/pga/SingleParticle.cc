//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/SingleParticle.hh"

namespace gex {
namespace pga {

SingleParticle::
SingleParticle(G4ParticleDefinition* p)
	: particle(p)
{
	// do nothing else
}

G4ParticleDefinition*
SingleParticle::
getParticleType(G4Event*)
{
	return particle;
}
	
} // namespace pga 	
} // namespace gex 
