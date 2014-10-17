//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_PRIMARY_VERTEX_SD_HH
#define GEX_SD_PRIMARY_VERTEX_SD_HH

#include "gex/sd/SDModule.hh"
#include "G4UserEventAction.hh"
#include "gex/ua/UserAction.hh"
#include "gex/data/PrimaryVertexData.hh"

namespace gex {
namespace sd {

/// \class PrimaryVertexSD
/// \brief A class used to store data about the primary vertex attached to an event.
///
/// PrimaryVertexSD is a sensitive detector which checks each G4Event's G4UserEventInformation for a data::NamedData containing a data::PrimaryVertexData called "primaryVertex". This class was created to store information about the primary vertex as attached to an G4Event by the primary generator action.
class PrimaryVertexSD : public SDModule, public G4UserEventAction, public ua::UserAction
{
public:
	typedef data::PrimaryVertexData DataType;
	PrimaryVertexSD(G4String name);
	virtual ~PrimaryVertexSD() {;}
	
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
