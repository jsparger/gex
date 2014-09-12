//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/SimTimeOfHitSD.hh"
#include "gex/util/make_unique.hh"
#include "gex/ua/UserActionManager.hh"
#include <iostream>
#include "G4Event.hh"
#include "gex/pga/CrappyEventInfo.hh"
#include "gex/data/UserInfoAccess.hh"
#include "gex/data/NamedData.hh"
#include "gex/util/Access.hh"
#include "gex/data/TimeData.hh"

namespace gex {
namespace sd {
	
SimTimeOfHitSD::
SimTimeOfHitSD(G4String name)
	: SDModule(name), data(nullptr), event(nullptr)
{
	// do nothing else
}

void 
SimTimeOfHitSD::
registerWith(ua::UserActionManager* ua)
{
	ua->addEventAction(this);
}

void 
SimTimeOfHitSD::
BeginOfEventAction(const G4Event* e)
{
	event = e;
}

G4bool
SimTimeOfHitSD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	// if (false == data->isSet && step->GetTotalEnergyDeposit() > 0)
	// {
	// 	data->isSet = true;
	// 	CrappyEventInfo* eventInfo = (CrappyEventInfo*)event->GetUserInformation();
	// 	data->time = step->GetTrack()->GetGlobalTime() + eventInfo->simulationTime;
	// }
	
	if (false == data->isSet && step->GetTotalEnergyDeposit() > 0)
	{
		data->isSet = true;
		data::UserInfoAccess<G4Event> infoAccess;
		try 
		{ 
			data::NamedData* nd = infoAccess.get(event);
			auto* simTime = util::get_access(*nd).get<data::TimeData>("simTime");
			data->time = step->GetTrack()->GetGlobalTime() + simTime->time;
		} 
		catch (std::exception& e)
		{
			throw std::runtime_error("SimTimeOfHitSD::ProcessHits(...) expect event to contain "
				"G4UserEventInformation containing a NamedData with a data::TimeData attached called simTime.");
		}
	}
	
	return false;
}

void
SimTimeOfHitSD::
Initialize(G4HCofThisEvent*)
{
	// do nothing
}

void
SimTimeOfHitSD::
EndOfEvent(G4HCofThisEvent*)
{
	// do nothing
}

std::unique_ptr<data::IData>
SimTimeOfHitSD::
createData()
{
	return std::make_unique<DataType>();
}

void
SimTimeOfHitSD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! SimTimeOfHitSD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}
	
} // namespace sd 
} // namespace gex 
