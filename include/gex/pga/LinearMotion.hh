//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_LINEAR_MOTION_HH
#define GEX_PGA_LINEAR_MOTION_HH 

#include "gex/pga/SpatialDistribution.hh"
#include "gex/util/TSAccumulator.hh"
#include "gex/pga/SpatialDistribution.hh"
#include "gex/pga/TimeDistribution.hh"

namespace gex {
namespace pga {

/// \class LinearMotion
/// \brief SpatialDistribution for a source moving at constant velocity. 
///
/// LinearMotion provides the spatial distribution for a source moving in a straight line with a constant speed. It uses an external simulation clock and a time distribution for particle emission to calculate the right position. LinearMotion will translate any other spatial distribution to this location. This means you may combine linear motion with a spatially distributed source.
class LinearMotion : public SpatialDistribution
{
public:
	typedef util::TSAccumulator<double> ClockType;
	
	/// Constructor. Takes a simulation clock \p clock, a SpatialDistribution \p stationarySpatial representing the spatial distribution the source would disregarding the linear motion component, a TimeDistribution \p timing which provides information about the elapsed time between particle emissions, a \p startPosition, \p direction of travel, and \p speed.
	LinearMotion(ClockType* clock, SpatialDistribution* stationarySpatial, TimeDistribution* timing, 
				G4ThreeVector startPosition, G4ThreeVector direction, double speed);
				
	virtual ~LinearMotion () {;}
	virtual G4ThreeVector getPosition(unsigned int nDecays = 1, G4Event* event = nullptr) override;

protected:
	ClockType* clock;
	SpatialDistribution* stationarySpatial;
	TimeDistribution* timing;
	G4ThreeVector startPosition, velocity;
};
	
} // namespace pga 
} // namespace gex 

#endif
