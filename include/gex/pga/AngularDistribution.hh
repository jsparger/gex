//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_ANGULAR_DISTRIBUTION_HH
#define GEX_PGA_ANGULAR_DISTRIBUTION_HH 

#include "G4ThreeVector.hh"
class G4Event;	

namespace gex {
namespace pga {

/// \class AngularDistribution
/// \brief Abstract base class for angular distributions.
class AngularDistribution
{
public:
	virtual ~AngularDistribution() {;}
	
	/// Sample a momentum direction.
	virtual G4ThreeVector getDirection(G4Event* event = nullptr) = 0;	
};

} // namespace pga 
} // namespace gex 

#endif

