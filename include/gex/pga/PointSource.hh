//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_POINT_SOURCE
#define GEX_PGA_POINT_SOURCE

#include "gex/pga/SpatialDistribution.hh"

namespace gex {
namespace pga {

/// \class PointSource
/// \brief Point source SpatialDistribution
///
/// PointSource is a SpatialDistribution which always returns a single point.
class PointSource : public SpatialDistribution
{
public:
	
	/// Constructor. Takes a single position for the source.
	PointSource(G4ThreeVector position)
		: pos(position)
	{
		// do nothing else
	}
	
	virtual ~PointSource () {;}
	
	virtual G4ThreeVector getPosition(unsigned int, G4Event*) override
	{
		return pos;
	}
	
protected:
	G4ThreeVector pos;
};

} // namespace pga 	
} // namespace gex 

#endif
