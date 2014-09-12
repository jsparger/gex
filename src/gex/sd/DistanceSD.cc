//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/DistanceSD.hh"
#include "gex/util/make_unique.hh"
#include "gex/ua/UserActionManager.hh"
#include <iostream>
#include "G4Event.hh"
#include "gex/pga/CrappyEventInfo.hh"
#include "gex/data/UserInfoAccess.hh"
#include "gex/data/NamedData.hh"
#include "gex/util/Access.hh"
#include "gex/data/PositionData.hh"

namespace gex {
namespace sd {
	
DistanceSD::
DistanceSD(G4String name)
	: SDModule(name), data(nullptr), event(nullptr)
{
	// do nothing else
}

void 
DistanceSD::
registerWith(ua::UserActionManager* ua)
{
	ua->addEventAction(this);
}

void 
DistanceSD::
BeginOfEventAction(const G4Event* e)
{
	event = e;
}

G4bool
DistanceSD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	if (false == data->isValid && step->GetTotalEnergyDeposit() > 0)
	{
		data::UserInfoAccess<G4Event> infoAccess;
		try 
		{ 
			data::NamedData* nd = infoAccess.get(event);
			auto* distance = util::get_access(*nd).get<data::PositionData>("distance");
			*data = *distance;
			data->isValid = true;
		} 
		catch (std::exception& e)
		{
			throw std::runtime_error("DistanceSD::ProcessHits(...) expect event to contain "
				"G4UserEventInformation containing a NamedData with a PositionData attached.");
		}
	}
	
	return false;
}

void
DistanceSD::
Initialize(G4HCofThisEvent*)
{
	// do nothing
}

void
DistanceSD::
EndOfEvent(G4HCofThisEvent*)
{
	// do nothing
}

std::unique_ptr<data::IData>
DistanceSD::
createData()
{
	return std::make_unique<DataType>();
}

void
DistanceSD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! DistanceSD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}
	
} // namespace sd 
} // namespace gex 
