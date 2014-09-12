//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sd/SDGroup.hh"
#include "gex/ua/RootTreeManager.hh"
#include "gex/data/RootDictionaryBuilder.hh"
#include "gex/ua/UserActionManager.hh"
#include "gex/ua/RunDataRegistration.hh"
#include "gex/util/make_unique.hh"

namespace gex {
namespace sd {

SDGroup::
SDGroup( G4String name )
	: G4VSensitiveDetector( name )
{
	// do nothing else
}

SDGroup&
SDGroup::
add(G4VSensitiveDetector* sd)
{
	sdVec.push_back(sd);
	return *this;
}

SDGroup&
SDGroup::
add(std::unique_ptr<G4VSensitiveDetector> sd)
{
	sdVec.push_back(sd.get());
	ownedSDVec.push_back(std::move(sd));
	return *this;
}

SDGroup&
SDGroup::
inform(data::DataModuleGroup* dataGroup)
{
	dataGroupVec.push_back(dataGroup);
	return *this;
}

std::string
SDGroup::
getKey(G4Step* step, G4TouchableHistory*)
{
	const G4VTouchable* touch = step->GetPreStepPoint()->GetTouchable();
	std::stringstream ss;
	ss << touch->GetVolume()->GetName() << touch->GetVolume()->GetCopyNo();
	return ss.str();
}

G4bool
SDGroup::
ProcessHits(G4Step* step, G4TouchableHistory* hist)
{
	if (step->GetTotalEnergyDeposit() > 0)
	{
		if (!dataGroupVec.empty())
		{
			const std::string& key = getKey(step, hist);
			for (auto* dataGroup : dataGroupVec)
			{
				dataGroup->setKey(key);
			}
		}
	
		for (auto* sd : sdVec)
		{
			// ProcessHits is protected. Hit will call ProcessHits.
			// hist will be null in all but one special case.
			sd->Hit(step); 
		}
	}
	// this return value doesn't seem to do anything
	return false;
}

void 
SDGroup::
Initialize(G4HCofThisEvent* hcote)
{
	for (auto* sd : sdVec)
	{
		sd->Initialize(hcote);
	}
}

void 
SDGroup::
EndOfEvent(G4HCofThisEvent* hcote)
{
	for (auto* sd : sdVec)
	{
		sd->EndOfEvent(hcote);
	}
}

void
SDGroup::
clear()
{
	for (auto* sd : sdVec)
	{
		sd->clear();
	}
}

void
SDGroup::
DrawAll()
{
	for (auto* sd : sdVec)
	{
		sd->DrawAll();
	}
}

void
SDGroup::
PrintAll()
{
	for (auto* sd : sdVec)
	{
		sd->PrintAll();
	}
}

	
} // namespace sd 
} // namespace gex 














