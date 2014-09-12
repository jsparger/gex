//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/TimeOfHitSD.hh"
#include "gex/util/make_unique.hh"
#include <iostream>

namespace gex {
namespace sd {
	
TimeOfHitSD::
TimeOfHitSD(G4String name)
	: SDModule(name), data(nullptr)
{
	// do nothing else
}
	
G4bool
TimeOfHitSD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	if (false == data->isSet && step->GetTotalEnergyDeposit() > 0)
	{
		data->isSet = true;
		data->time = step->GetTrack()->GetGlobalTime();
	}
	return false;
}

void
TimeOfHitSD::
Initialize(G4HCofThisEvent*)
{
	// do nothing
}

void
TimeOfHitSD::
EndOfEvent(G4HCofThisEvent*)
{
	// do nothing
}

std::unique_ptr<data::IData>
TimeOfHitSD::
createData()
{
	return std::make_unique<DataType>();
}

void
TimeOfHitSD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! TimeOfHitSD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}
	
} // namespace sd 
} // namespace gex 
