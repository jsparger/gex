//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_TIME_OF_HIT_SD
#define GEX_SD_TIME_OF_HIT_SD

#include "gex/sd/SDModule.hh"
#include "gex/data/TimeData.hh"

namespace gex {
namespace sd {

/// \class TimeOfHitSD
/// \brief Stores the global time of a hit in a detector volume.
///
/// TimeOfHitSD is a sensitive detector that will store the global time of a hit in a sensitive detector volume.
class TimeOfHitSD : public SDModule
{
public:
	typedef data::TimeData DataType;
	/// Constructor. Requires a name for the sensitive detector.
	TimeOfHitSD(G4String name);
	virtual ~TimeOfHitSD() {;}
	
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override;
	virtual void Initialize(G4HCofThisEvent* hcote) override;
	virtual void EndOfEvent(G4HCofThisEvent* hcote) override;
	
	virtual std::unique_ptr<data::IData> createData() override;
	virtual void setData(data::IData* data) override;
	
protected:
	DataType* data;
};
	
} // namespace sd 	
} // namespace gex 

#endif
