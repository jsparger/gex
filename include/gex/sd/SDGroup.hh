//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_SDGROUP
#define GEX_SD_SDGROUP 

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "gex/data/DataModuleGroup.hh"
#include <vector>
#include <memory>

namespace gex {
/// The sd namespace.
namespace sd {

/// \class SDGroup
/// \brief A class which allows more than one G4VSensitiveDetector to be attached to a volume.
///
/// SDGroup allows for multiple G4VSensitiveDetectors to be attached to a volume. Sensitive detectors are added to the SDGroup, which is then set as the volume's sensitive detector. The SDGroup class then forwards calls to each member of the group.
	
class SDGroup : public G4VSensitiveDetector
{
public:
	/// Constructor. Requires a \p name for the SDGroup.
	SDGroup(G4String name);
	virtual ~SDGroup() {;}
	
	/// add a G4VSensitiveDetector \p sd and transfer its ownership to the SDGroup.
	virtual SDGroup& add(std::unique_ptr<G4VSensitiveDetector> sd);
	/// add a G4VSensitiveDetector
	virtual SDGroup& add(G4VSensitiveDetector* sd);
	/// add a DataModuleGroup for this SDGroup to inform.
	virtual SDGroup& inform(data::DataModuleGroup* dataGroup);
	
	virtual void Initialize(G4HCofThisEvent* hcote) override;
	virtual void EndOfEvent(G4HCofThisEvent* hcote) override;
	virtual void clear() override;
	virtual void DrawAll() override;
	virtual void PrintAll() override;
	
protected:
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override;
	virtual std::string getKey(G4Step* step, G4TouchableHistory* hist);
	
	std::vector<data::DataModuleGroup*> dataGroupVec;
	std::vector<G4VSensitiveDetector*> sdVec;
	std::vector<std::unique_ptr<G4VSensitiveDetector>> ownedSDVec;
};

// \related SDGroup
// \brief Create a SDGroup, assign it to the volume, and register it with Geant4. Name must be unique.
SDGroup* make_sensitive(G4LogicalVolume* vol, std::string name);

	
} // namespace sd 	
} // namespace gex 

#endif
