//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_SDMODULE_HH
#define GEX_SD_SDMODULE_HH 

#include "G4VSensitiveDetector.hh"
#include "gex/data/DataModule.hh"

namespace gex {
namespace sd {

/// \class SDModule
/// \brief Abstract base class combining G4VSensitiveDetector and DataModule

struct SDModule : public G4VSensitiveDetector, public data::DataModule
{
public:
	SDModule(G4String name)
		: G4VSensitiveDetector(name), DataModule(name)
	{
		// do nothing else
	}
	
	virtual ~SDModule() {;}
	// make ProcessHits public. It is protected in G4VSensitiveDetector.
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override = 0;
	
	// just list these for reference
	virtual std::unique_ptr<data::IData> createData() override = 0;
	virtual void setData(data::IData* data) override = 0;
};
	
} // namespace sd 	
} // namespace gex 

#endif
