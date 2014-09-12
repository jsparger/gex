//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/DetectorIdentitySD.hh"
#include "gex/util/make_unique.hh"
#include "G4MTRunManager.hh"
#include "G4StepPoint.hh"
#include "G4VPhysicalVolume.hh"

namespace gex {
namespace sd {

DetectorIdentitySD::
DetectorIdentitySD(G4String name)
	: SDModule(name), data(nullptr)
{
	// do nothing else
}
	
G4bool
DetectorIdentitySD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	if (false == data->isSet)
	{
		data->name = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
		data->copyNumber = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
		data->isSet = true;
	}
	return false;
}

std::unique_ptr<data::IData>
DetectorIdentitySD::
createData()
{
	return std::make_unique<DataType>();
}

void
DetectorIdentitySD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! DetectorIdentitySD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}

} // namespace sd 
} // namespace gex 
