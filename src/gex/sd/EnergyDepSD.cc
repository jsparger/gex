//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/EnergyDepSD.hh"
#include "gex/util/make_unique.hh"
#include <iostream>

namespace gex {
namespace sd {
	
EnergyDepSD::
EnergyDepSD(G4String name)
	: SDModule(name), data(nullptr)
{
	// do nothing else
}
	
G4bool
EnergyDepSD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	data->energy += step->GetTotalEnergyDeposit();
	//std::cout << "data->energy = " << data->energy << "\n";
	return false;
}

void
EnergyDepSD::
Initialize(G4HCofThisEvent*)
{
	// do nothing
}

void
EnergyDepSD::
EndOfEvent(G4HCofThisEvent*)
{
	// do nothing
}

std::unique_ptr<data::IData>
EnergyDepSD::
createData()
{
	return std::make_unique<data::EnergyData>();
}

void
EnergyDepSD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! EnergyDepSD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}
	
} // namespace sd 
} // namespace gex 
