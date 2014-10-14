#include "MyDetector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

void 
MyDetector::
construct(G4LogicalVolume* world)
{
	// Get G4NistManager which makes the built-in G4 materials.
	G4NistManager* nistMan = G4NistManager::Instance();
	// Create sodium iodide detector's shape.
	G4Box* NaIDetector_solid = new G4Box("naiBox",10*cm,10*cm,10*cm);
	// Create sodium iodide logical volume. We store this as a member variable.
	NaIDetector_logV = new G4LogicalVolume(NaIDetector_solid, nistMan->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "naiLog");
	// Place the sodium iodide detector at the origin.
	new G4PVPlacement(0, G4ThreeVector(0,0,0), NaIDetector_logV, "naiPhys", world, false,	0);
}

void
MyDetector::
constructSDAndField(sd::Sensitivizer*)
{
	// Make the sodium iodide detector sensitive.
	sens->makeSensitive(NaIDetector_logV);
}
	