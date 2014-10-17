//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/DetectorPositionSD.hh"
#include "gex/util/make_unique.hh"
#include "G4MTRunManager.hh"

namespace gex {
namespace sd {

DetectorPositionSD::
DetectorPositionSD(G4String name)
	: SDModule(name), data(nullptr), navigator(new G4Navigator())
{
	navigator->SetWorldVolume(G4MTRunManager::GetMasterRunManagerKernel()->GetCurrentWorld());
}
	
G4bool
DetectorPositionSD::
ProcessHits(G4Step* step, G4TouchableHistory*)
{
	if (false == data->isValid)
	{
		G4ThreeVector stepPos = step->GetPreStepPoint()->GetPosition();
		navigator->LocateGlobalPointAndSetup(stepPos);
		G4ThreeVector detPos = navigator->NetTranslation();
		data->x = detPos.x();
		data->y = detPos.y();
		data->z = detPos.z();
		data->isValid = true;
	}
	return false;
}

std::unique_ptr<data::IData>
DetectorPositionSD::
createData()
{
	return std::make_unique<DataType>();
}

void
DetectorPositionSD::
setData(data::IData* d)
{
	data = dynamic_cast<DataType*>(d);
		
	if (nullptr == data)
	{
		std::cerr << "Error! DetectorPositionSD::setData(...), data is not of correct type.\n";
		std::exit(0);
		// TODO: throw real exception
	}
}

} // namespace sd 
} // namespace gex 
