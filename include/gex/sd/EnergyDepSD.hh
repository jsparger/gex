//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_ENERGY_DEP_SD_HH
#define GEX_SD_ENERGY_DEP_SD_HH

#include "gex/sd/SDModule.hh"
#include "gex/data/EnergyData.hh"

namespace gex {
namespace sd {

/// \class EnergyDepSD
/// \brief Accumulates the energy deposited in a detector.
///
/// EnergyDepSD is a sensitive detector which will accumulate the energy deposited in a volume. It stores this number in a data::EnergyData object.
class EnergyDepSD : public SDModule
{
public:
	typedef data::EnergyData DataType;
	
	/// Constructor. Requires a name for the sensitive detector.
	EnergyDepSD(G4String name);
	virtual ~EnergyDepSD() {;}
	
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
