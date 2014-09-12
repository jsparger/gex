//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_SIM_TIME_OF_HIT_SD
#define GEX_SD_SIM_TIME_OF_HIT_SD

#include "gex/sd/SDModule.hh"
#include "G4UserEventAction.hh"
#include "gex/ua/UserAction.hh"
#include "gex/data/TimeData.hh"

namespace gex {
namespace sd {

/// \class SimTimeOfHitSD
/// \brief Stores the time of a hit according to some user defined simulation clock.
///
/// SimTimeOfHitSD is a sensitive detector which checks each G4Event's G4UserEventInformation for a data::NamedData containing a data::TimeData called "simTime". This class was created to store the time of a hit according to some user defined simulation clock (as opposed to Geant4's clock which resets to zero at the beginning of each event).
class SimTimeOfHitSD : public SDModule, public G4UserEventAction, public ua::UserAction
{
public:
	typedef data::TimeData DataType;
	/// Constructor. Requires a name for the sensitive detector.
	SimTimeOfHitSD(G4String name);
	virtual ~SimTimeOfHitSD() {;}
	
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
