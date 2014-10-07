//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/LinearMotion.hh"
#include <iostream>
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "gex/pga/CrappyEventInfo.hh"
#include "gex/data/UserInfoAccess.hh"
#include "gex/data/NamedData.hh"
#include "gex/data/TimeData.hh"
#include "gex/data/PositionData.hh"
#include "gex/util/Access.hh"

namespace gex {
namespace pga {
	
LinearMotion::
LinearMotion(ClockType* c, SpatialDistribution* pos, TimeDistribution* t, G4ThreeVector start, G4ThreeVector direction, double speed)
	: clock(c), stationarySpatial(pos), timing(t), startPosition(start), velocity(direction.unit()*speed)
{
	// do nothing else
}

G4ThreeVector
LinearMotion::
getPosition(unsigned int nDecays, G4Event* event)
{
	double dt = timing->getTime(nDecays, event);
	double time = clock->accumulate(dt);
	G4ThreeVector basePosition = startPosition + velocity*time;
	G4ThreeVector position =  basePosition + stationarySpatial->getPosition();
	
	// CrappyEventInfo* eventInfo = new CrappyEventInfo();
	// eventInfo->simulationTime = time;
	// event->SetUserInformation(eventInfo);
	data::UserInfoAccess<G4Event> infoAccess;
	if (infoAccess.hasData(event))
	{
		data::NamedData* nd = infoAccess.get(event);
		auto access = util::get_access(*nd);
	
		auto* simTime = new data::TimeData();
		simTime->time = time;
		access.insert("simTime", simTime);
		
		auto* posData = new data::PositionData();
		posData->x = basePosition.x();
		posData->y = basePosition.y();
		posData->z = basePosition.z();
		access.insert("sourcePos", posData);
		
		auto* distance = new data::PositionData();
		distance->x = velocity.mag()*time;
		access.insert("distance", distance);
	}
	
	return position;
}

} // namespace pga 
} // namespace gex 
