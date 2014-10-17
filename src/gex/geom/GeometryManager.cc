//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/geom/GeometryManager.hh"
#include "G4VPhysicalVolume.hh"

namespace gex {
namespace geom {

GeometryManager::
GeometryManager(G4VPhysicalVolume* world, sd::Sensitivizer* sens)
: worldPhys(world), sensitivizer(sens)
{
	// do nothing else
}

void
GeometryManager::
addGeometry(std::unique_ptr<Geometry> geom)
{
	geometryVec.push_back(std::move(geom));
}

G4VPhysicalVolume*
GeometryManager::
Construct()
{
	G4LogicalVolume* worldLog = worldPhys->GetLogicalVolume();
	
	for (auto& geom : geometryVec)
	{
		geom->construct(worldLog);
	}
	
	return worldPhys;
}

void
GeometryManager::
ConstructSDandField()
{
	for (auto& geom : geometryVec)
	{
		geom->constructSDAndField(sensitivizer);
	}
}


} // namespace geom
} // namespace gex
