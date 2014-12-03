//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef MY_USER_ACTION_INITIALIZATION_HH
#define MY_USER_ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include <gex/util/TSAccumulator.hh>
#include <gex/ua/UserActionManager.hh>
#include <memory>
#include <string>

/// \class MyUserActionInitialization
/// \brief An example user action initialization employing gex.
///
/// This class is an example user action initialization that uses the gex library to set up the simulation's user actions and data output.
class MyUserActionInitialization : public G4VUserActionInitialization
{
public:	
	/// Constructor. Requires a filename for a Cern ROOT file and a simulation clock.
	MyUserActionInitialization(const std::string& fname);
	
	/// Destructor. Does nothing.
	virtual ~MyUserActionInitialization() {;}
	
	/// From G4VUserActionInitialization. Used to set up worker threads.
	virtual void Build() const override;
	
	/// From G4VUserActionInitialization. Used to set up the master thread.
	virtual void BuildForMaster() const override;
	
protected:
	
	/// The name we will use as a base for our Cern ROOT file.
	std::string fileName;
};

#endif