//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/geom/BoxWorld.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

namespace gex {
namespace geom {
	
BoxWorld::
BoxWorld(double x, double y, double z)
	: hx(x), hy(y), hz(z), material(nullptr)
{
	// do nothing else
}

G4VPhysicalVolume*
BoxWorld::
construct()
{
	if (!material)
	{
		G4NistManager* man = G4NistManager::Instance();
		material = man->FindOrBuildMaterial("G4_AIR");
	}
	
	G4Box* worldSolid = new G4Box("worldSolid",hx,hy,hz);
	G4LogicalVolume* worldLog = new G4LogicalVolume(worldSolid, material, "worldLog");
	G4VPhysicalVolume* worldPhys = 
						new G4PVPlacement(0,                       
	                        G4ThreeVector(0, 0, 0),                        
	                        worldLog,              
	                        "WorldPhys",               
	                        0,                
	                        false,                   
	                        0);
							
	return worldPhys;                      
}
	
} // namespace geom 	
} // namespace gex 
