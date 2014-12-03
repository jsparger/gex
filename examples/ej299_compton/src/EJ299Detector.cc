#include "EJ299Detector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"

void 
MyDetector::
construct(G4LogicalVolume* world)
{
	// Get G4NistManager which makes the built-in G4 materials.
	G4NistManager* nistMan = G4NistManager::Instance();
	
	// Create aluminum casing shape
	auto casing_solid = new G4Box("casing", 5.5*cm, 5.5*cm, 3.2*cm);
	
	// Create ej299 detector shape
	auto ej299_solid = new G4Box("detector", 5.24*cm, 5.24*cm, 2.54*cm);
	
	// Create ej299 detector material
	double density = 1.08*g/cm3;
	int hydrogen = 1; //Hydrogen
	int carbon = 6; //Carbon
	auto ej299 = new G4Material("ej299", density, ncomponents=2);
	ej299->AddElement(manager->FindOrBuildElement(hydrogen), 19);
	ej299->AddElement(manager->FindOrBuildElement(carbon), 18);
   
	// Create casing logical volume. We store this as a member variable.
	casing_logV = new G4LogicalVolume(casing_solid, nistMan->FindOrBuildMaterial("G4_ALUMINUM"), "casingLog");
   
	// Create ej299 logical volume. We store this as a member variable.
	ej299_logV = new G4LogicalVolume(ej299_solid, ej299, "ej299Log");
	
	// Place casing in world volume at origin.
	new G4PVPlacement(0, G4ThreeVector(0,0,0), casing_logV, "casingPhys", world, false, 0);
	
	// Place the ej299 volume inside casing at casing origin.
	new G4PVPlacement(0, G4ThreeVector(0,0,0), ej299_logV, "ej299Phys", casing_logV, false, 0);
}

void
MyDetector::
constructSDAndField(gex::sd::Sensitivizer* sens)
{
	// Make the sodium iodide detector sensitive.
	sens->makeSensitive(NaIDetector_logV);
}