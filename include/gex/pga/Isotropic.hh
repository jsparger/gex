//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_ISOTROPIC_HH
#define GEX_PGA_ISOTROPIC_HH 

#include "gex/pga/AngularDistribution.hh"

namespace gex {
namespace pga {
	
/// \class Isotropic
/// \brief An isotropic angular distribution
///
/// Isotropic is an angular distribution which uniformly samples directions from the surface a sphere. Use this distribution if your source emits particles in all directions with the same probability.
class Isotropic : public AngularDistribution
{
public:
	virtual ~Isotropic() {;}
	G4ThreeVector getDirection(G4Event* event = nullptr) override;
};	

} // namespace pga 	
} // namespace gex 

#endif
