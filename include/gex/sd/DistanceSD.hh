//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_DISTANCE_SD_HH
#define GEX_SD_DISTANCE_SD_HH

#include "gex/sd/SDModule.hh"
#include "G4UserEventAction.hh"
#include "gex/ua/UserAction.hh"
#include "gex/data/PositionData.hh"

namespace gex {
namespace sd {
	
/// \class DistanceSD
/// \brief Stores position data attached to the G4Event.  
///
/// DistanceSD is a sensitive detector which checks each G4Event's G4UserEventInformation for a data::NamedData containing a data::Position data called "distance". This class was created to store the location of a moving source. In this case, the event information is attached by the primary generator action.
class DistanceSD : public SDModule, public G4UserEventAction, public ua::UserAction
{
public:
	typedef data::PositionData DataType;
	
	/// Constructor. Requires a name for the sensitive detector.
	DistanceSD(G4String name);
	virtual ~DistanceSD() {;}
	
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override;
	virtual void Initialize(G4HCofThisEvent* hcote) override;
	virtual void EndOfEvent(G4HCofThisEvent* hcote) override;
	
	virtual void BeginOfEventAction(const G4Event* event) override;
	
	virtual void registerWith(ua::UserActionManager* ua) override;
	
	virtual std::unique_ptr<data::IData> createData() override;
	virtual void setData(data::IData* data) override;
	
protected:
	DataType* data;
	const G4Event* event;
};
	
} // namespace sd 
} // namespace gex 


#endif
