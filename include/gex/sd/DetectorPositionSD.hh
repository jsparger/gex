//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_DETECTOR_POSITION_SD_HH
#define GEX_SD_DETECTOR_POSITION_SD_HH

#include "gex/sd/SDModule.hh"
#include "gex/data/PositionData.hh"
#include "G4Navigator.hh"

namespace gex {
namespace sd {

/// \class DetectorPositionSD
/// \brief Gets the world coordinates of a sensitive volume after a hit.
///
///	DetectorPositionSD is a sensitive detector which will store the world coordinates of a sensitive volume after a hit.
class DetectorPositionSD : public SDModule
{
public:
	typedef data::PositionData DataType;
	
	/// Constructor. Requries a name for the sensitive detector.
	DetectorPositionSD(G4String name);
	~DetectorPositionSD() {;}
	
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override;
	virtual std::unique_ptr<data::IData> createData() override;
	virtual void setData(data::IData* data) override;
	
protected:
	DataType* data;
	G4Navigator* navigator; // don't delete this. Causes corrupt double linked list error if you do.
};
	
} // namespace sd 	
} // namespace gex 

#endif
