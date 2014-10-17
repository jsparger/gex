//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "MyUserActionInitialization.hh"

#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"

#include <gex/ua/UserActionManager.hh>
#include <gex/ua/RootTreeManager.hh>
#include <gex/ua/Callback.hh>
#include <gex/pga/PointSource.hh>
#include <gex/pga/Isotropic.hh>
#include <gex/pga/MonoEnergyDist.hh>
#include <gex/pga/SingleParticle.hh>
#include <gex/pga/GenericSource.hh>
#include <gex/create.hh>

MyUserActionInitialization::
MyUserActionInitialization(const std::string& fname, std::unique_ptr<ClockType> c)
	: fileName(fname), clock(std::move(c))
{
	// We have initialized out filename and clock. The clock must be initialized using std::move because std::unique_ptr is not copyable.
	// do nothing else.
}

void
MyUserActionInitialization::
Build() const
{
	// We will set the user actions for the worker threads in this method.
	
	// -- Get the thread local UserActionManager:
	// In Gex, we will register our user actions with this class instead of the G4RunManager. Unlike the G4RunManager, UserActionManager lets us have more than one of each type of user action if we wish. This allows each user action to have a single, specific job.
	auto* uam = gex::ua::UserActionManager::GetUserActionManager();
	
	// -- Set up the Cern ROOT file for data storage:
	// Get the RootTreeManager for the fileName. Register the RootTreeManager with the UserActionManager so it works.
	auto* rtm = gex::ua::RootTreeManager::GetRootTreeManager(fileName);
	uam->registerAction(rtm);
	
	// -- Build the source:
	
	// Create a struct to hold all the distributions for our source. Initialize the distributions as we like. In this case, we create an isotropic point source at 1 meter down the x-axis which emits 0.5 MeV gamma rays. 
	struct SourceConfig {
		gex::pga::PointSource pointSource = {G4ThreeVector(1*m,0,0)};
		gex::pga::Isotropic isotropic;
		gex::pga::MonoEnergyDist monoEnergy = {0.5*MeV};
		gex::pga::SingleParticle singleParticle = {G4Gamma::Definition()};
	};
	
	// Create a SourceConfig and let the UserActionManager adopt it. We do this because we need the distributions in our SourceConfig to live for the duration of the simulation. If the UserActionManager did not adopt the SourceConfig, it would be deleted at the end of this Build() method.
	auto* sourceConfig = gex::create<SourceConfig>();
	
	// create a generic source using the distributions in our source configuration.
	auto* source = new gex::pga::GenericSource(
		&sourceConfig->monoEnergy,
		&sourceConfig->isotropic,
		&sourceConfig->pointSource,
		&sourceConfig->singleParticle);
	
	// TODO: Can UserActionManager do sources?
	// give our source to geant4.
	SetUserAction(source);
}

void 
MyUserActionInitialization::
BuildForMaster() const
{
	using namespace gex;
	// We will set the user actions for the master thread in this method.

	// -- Set up an action that will reset the clock at the beginning of each run.
	// create a function to reset our clock.
	auto clockptr = clock.get();
	auto clockResetFcn = [clockptr] { clockptr->reset(); };

	// register our clock reset function to be called at the beginning of each run.
	gex::create<ua::Callback>(clockResetFcn, std::set<ua::Cycle>{gex::ua::Cycle::RUN_BEGIN});
}





