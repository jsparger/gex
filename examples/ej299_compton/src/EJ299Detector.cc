#include "EJ299Detector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"

void 
EJ299Detector::
construct(G4LogicalVolume* world)
{
	// Get G4NistManager which makes the built-in G4 materials.
	G4NistManager* nistMan = G4NistManager::Instance();
	
	// size of scintillator
	double ejWidth = 97.5*mm;
	double ejDepth = 40*mm;
	
	// size of case.
	double alThickness = 3*mm;
	double caseWidth = ejWidth + 2*alThickness; // aluminum on both sides
	double caseDepth = ejDepth + alThickness; // aluminum only in front
	
	// Create aluminum casing shape
	auto casing_solid = new G4Box("casing", caseWidth/2, caseWidth/2, caseDepth/2);
	
	// Create ej299 detector shape
	auto ej299_solid = new G4Box("detector", ejWidth/2, ejWidth/2, ejDepth/2);
	
	// Create ej299 detector material
	double density = 1.08*g/cm3;
	int hydrogen = 1; //Hydrogen
	int carbon = 6; //Carbon
	auto ej299 = new G4Material("ej299", density, 2);
	ej299->AddElement(nistMan->FindOrBuildElement(hydrogen), 19);
	ej299->AddElement(nistMan->FindOrBuildElement(carbon), 18);
   
	// Create casing logical volume made of aluminum.
	auto casing_logV = new G4LogicalVolume(casing_solid, nistMan->FindOrBuildMaterial("G4_Al"), "casingLog");
   
	// Create ej299 logical volume. We store this as a member variable.
	ej299_logV = new G4LogicalVolume(ej299_solid, ej299, "ej299Log");
	
	// Place casing in world volume at origin.
	new G4PVPlacement(0, G4ThreeVector(0,0,0), casing_logV, "casingPhys", world, false, 0);
	
	// Place the ej299 volume inside casing. Offset in z direction so scintillator touches -z edge of case (zero aluminum volume in back).
	new G4PVPlacement(0, G4ThreeVector(0,0,-alThickness/2), ej299_logV, "ej299Phys", casing_logV, false, 0);
}

void
EJ299Detector::
constructSDAndField(gex::sd::Sensitivizer* sens)
{
	// Make the sodium iodide detector sensitive.
	sens->makeSensitive(ej299_logV);
}