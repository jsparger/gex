//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_MOCK_DUMMY_PRIMARY_GENERATOR_HH
#define GEX_SIM_MOCK_DUMMY_PRIMARY_GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include <iostream>
#include <thread>
#include <chrono>

namespace gex {
namespace sim {
namespace mock {

/// \class DummyPrimaryGenerator
/// \brief Mock primary generator action.
///
/// Generates no primaries. Sleeps for 20 milliseconds per event to simulate work.
class DummyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	virtual ~DummyPrimaryGenerator()
	{
		std::cout << "~DummyPrimaryGenerator() called!\n";
	}
	virtual void GeneratePrimaries(G4Event*) override
	{
		// pretend to work
		std::chrono::milliseconds dura(20);
		std::this_thread::sleep_for(dura);
	}
};

} // namespace mock 
} // namespace test
} // namespace gex

#endif
