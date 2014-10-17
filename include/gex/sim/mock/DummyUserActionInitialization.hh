//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_MOCK_DUMMYUSERACTIONINITIALIZATION_HH
#define GEX_SIM_MOCK_DUMMYUSERACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "gex/sim/mock/DummyPrimaryGenerator.hh"
#include "gex/sim/mock/DummyRunAction.hh"
#include <iostream>

namespace gex {
namespace sim {
namespace mock {

/// \class DummyUserActionInitialization
/// \brief Mock user action initialization.
///
/// Sets the primary generator action to DummyPrimaryGenerator and the run action to DummyRunAction.
class DummyUserActionInitialization : public G4VUserActionInitialization
{
public:
	virtual ~DummyUserActionInitialization()
	{
		std::cout << "~DummyUserActionInitialization() called!\n";
	}
	
	void Build() const override
	{
		SetUserAction(new gex::sim::mock::DummyPrimaryGenerator());
		SetUserAction(new gex::sim::mock::DummyRunAction());
	}
	
	void BuildForMaster() const override
	{
		SetUserAction(new gex::sim::mock::DummyRunAction());
	}
	
};

} // namespace mock 
} // namespace test
} // namespace gex

#endif
