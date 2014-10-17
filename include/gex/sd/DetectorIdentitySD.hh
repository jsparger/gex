//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_DETECTOR_IDENTITY_SD_HH
#define GEX_SD_DETECTOR_IDENTITY_SD_HH

#include "gex/sd/SDModule.hh"
#include "gex/data/DetectorData.hh"
#include "G4Navigator.hh"

namespace gex {
namespace sd {

/// \class DetectorIdentitySD
/// \brief Stores the name and copy number of a detector volume after a hit.
///
///	DetectorIdentitySD is a sensitive detector that will store the name and copy number of a sensitive volume when it is hit. This is useful if the same sensitive detector is applied to multiple volumes.
class DetectorIdentitySD : public SDModule
{
public:
	typedef data::DetectorData DataType;
	
	/// Constructor. Requires a name for the sensitive detector.
	DetectorIdentitySD(G4String name);
	~DetectorIdentitySD() {;}
	
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override;
	virtual std::unique_ptr<data::IData> createData() override;
	virtual void setData(data::IData* data) override;
	
protected:
	DataType* data;
};
	
} // namespace sd 	
} // namespace gex 

#endif
