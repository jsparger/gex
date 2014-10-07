//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_MOCK_DUMMY_SENSITIVIZER_HH
#define GEX_SIM_MOCK_DUMMY_SENSITIVIZER_HH

#include "gex/sd/Sensitivizer.hh"

namespace gex {
namespace sim {
namespace mock {
	
/// \class DummySensitivizer
/// \brief Mock sensitivizer.
class DummySensitivizer : public sd::Sensitivizer
{
public:
	virtual ~DummySensitivizer() {;}
	virtual void makeSensitive(G4LogicalVolume*) override 
	{
		// do nothing
	}
};

} // namespace mock 
} // namespace test
} // namespace gex

#endif
