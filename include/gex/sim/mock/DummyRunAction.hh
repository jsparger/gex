//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_MOCK_DUMMYRUNACTION_HH
#define GEX_SIM_MOCK_DUMMYRUNACTION_HH

#include "G4UserRunAction.hh"
#include <iostream>

namespace gex {
namespace sim {
namespace mock {

/// \class DummyRunAction
/// \brief Mock run action.
///
/// Does nothing except print to standard out at the beginning and end of runs.
class DummyRunAction : public G4UserRunAction
{
public:
	virtual ~DummyRunAction()
	{
		std::cout << "~DummyRunAction() called!\n";
	}
	
	virtual void BeginOfRunAction(const G4Run*)override
	{
		if (false == this->IsMaster())
		{
			std::cout << "DummyRunAction::BeginOfRunAction(...) called!\n";
		}
		else
		{
			std::cout << "DummyRunAction::BeginOfRunAction(...) MASTER called!\n";
		}
	}
	
	virtual void EndOfRunAction(const G4Run*) override 
	{
		if (false == this->IsMaster())
		{
			std::cout << "DummyRunAction::EndOfRunAction(...) called!\n";
		}
		else
		{
			std::cout << "DummyRunAction::EndOfRunAction(...) MASTER called!\n";
		}
	}
};

} // namespace mock 
} // namespace test
} // namespace gex


#endif
