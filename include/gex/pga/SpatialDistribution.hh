//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_SPATIALDISTRIBUTION_HH
#define GEX_PGA_SPATIALDISTRIBUTION_HH 

#include "G4ThreeVector.hh"
class G4Event;

namespace gex {
namespace pga {

/// \class SpatialDistribution
/// \brief Abstract base class for spatial distributions.
class SpatialDistribution
{
public:
	virtual ~SpatialDistribution() {;}
	
	// TODO: nDecays parameter is a hack to allow for motion and vetoed events. This functionality should be added in a less intrusive way.
	/// Sample a position. Get the position after \p nDecays emissions. 
	virtual G4ThreeVector getPosition(unsigned int nDecays = 1, G4Event* event = nullptr) = 0;
};
	
} // namespace pga 
} // namespace gex 

#endif

