//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_GEOM_GEOMETRY_HH
#define GEX_GEOM_GEOMETRY_HH

#include "gex/sd/Sensitivizer.hh"
#include "G4LogicalVolume.hh"

namespace gex {
namespace geom {

/// \class Geometry
/// \brief Abstract base class for Geometries which work with GeometryManager
///
///
class Geometry
{
public:
	virtual ~Geometry(){;}
	
	/// this method should construct the geometry within the world volume provided. It invoked in the master thread.
	virtual void construct(G4LogicalVolume* world) = 0;
	
	/// this method should construct all sensitive detectors and fields with the Sensitivizer provided. They are *thread local* and this method is invoked for each thread.
	virtual void constructSDAndField(sd::Sensitivizer*) {;}
};

} // namespace geom
} // namespace gex

#endif
