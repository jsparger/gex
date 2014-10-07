//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_MOCK_DUMMYDETECTORCONSTRUCTION_HH
#define GEX_SIM_MOCK_DUMMYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include <iostream>

namespace gex {
namespace sim {
namespace mock {

/// \class DummyDetectorConstruction
/// \brief Mock detector construction.
class DummyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	virtual ~DummyDetectorConstruction()
	{
		std::cout << "~DummyDetectorConstruction() called! \n";
	}
	
	G4VPhysicalVolume* Construct() override
	{
		std::cout << "DummyDetectorConstruction::Construct() called!\n";
		
		G4NistManager* man = G4NistManager::Instance();
		G4Material* Air  = man->FindOrBuildMaterial("G4_AIR");
		G4Box* worldSolid = new G4Box("worldSolid",100*m,50*m,100*m);
		G4LogicalVolume* worldLog = new G4LogicalVolume(worldSolid, Air, "worldLog");
		G4VPhysicalVolume* worldPhys
		    = new G4PVPlacement(0,                       
		                        G4ThreeVector(0, 0, 0),                        
		                        worldLog,              
		                        "WorldPhys",               
		                        0,                
		                        false,                   
		                        0);  
		return worldPhys;
	}
	
	virtual void ConstructSDandField() override
	{
		std::cout << "DummyDetectorConstruction::ConstructSDandField() called!\n";
	}
};

} // namespace mock 
} // namespace test
} // namespace gex

#endif
