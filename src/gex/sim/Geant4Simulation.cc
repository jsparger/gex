//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/sim/Geant4Simulation.hh"

#include "G4RunManager.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4MTRunManager.hh"
#include "gex/sim/mock/DummyUserActionInitialization.hh"
#include "gex/sim/mock/DummyDetectorConstruction.hh"
#include "QGSP_BIC.hh"
#include <iostream>
#include "Randomize.hh"
#include "G4UImanager.hh"
#ifdef G4VIS_USE
 #include "G4VisExecutive.hh"
#endif
#include <sstream>

namespace gex {
namespace sim {

Geant4Simulation::
Geant4Simulation(bool isMultiThreaded, unsigned int nt)
: 	runManager(nullptr), 
	useDefaultUserActionInitialization(true), 
	useDefaultPhysics(true), 
	useDefaultDetectorConstruction(true),
	userActionInitialization(nullptr),
	physicsList(nullptr), 
	detectorConstruction(nullptr), 
	numThreads(nt), 
	numEvents(1)
{
	// set the run manager
	if (isMultiThreaded)
	{
		G4MTRunManager* rm = new G4MTRunManager();
		rm->SetNumberOfThreads(numThreads);
		runManager = std::unique_ptr<G4RunManager>(rm);
	}
	else
	{
		runManager = std::unique_ptr<G4RunManager>(new G4RunManager());
	}
}

Geant4Simulation::
~Geant4Simulation()
{
	// do nothing
	std::cout << "~Geant4Simulation() called!\n";
}

Geant4Simulation&
Geant4Simulation::
setUserActionInitialization(G4VUserActionInitialization* action)
{
	useDefaultUserActionInitialization = false;
	userActionInitialization = action;
	return *this;
}

Geant4Simulation&
Geant4Simulation::
setPhysicsList(G4VUserPhysicsList* p)
{
	useDefaultPhysics = false;
	physicsList = p;
	return *this;
}

Geant4Simulation&
Geant4Simulation::
setDetectorConstruction(G4VUserDetectorConstruction* dc)
{
	useDefaultDetectorConstruction = false;
	detectorConstruction = dc;
	return *this;
}

Geant4Simulation&
Geant4Simulation::
setNumberOfEvents(unsigned int ne)
{
	numEvents = ne;
	return *this;
}

void
Geant4Simulation::
initialize()
{	
	if (useDefaultUserActionInitialization)
	{
		userActionInitialization = new mock::DummyUserActionInitialization();
	}
	
	if (useDefaultPhysics)
	{
		physicsList = new QGSP_BIC();
	}
	
	if (useDefaultDetectorConstruction)
	{
		detectorConstruction = new mock::DummyDetectorConstruction();	
	}

	// set the stuff
	runManager->SetUserInitialization(detectorConstruction);
	runManager->SetUserInitialization(physicsList);
	runManager->SetUserInitialization(userActionInitialization);
	runManager->Initialize();
}

void
Geant4Simulation::
execute()
{
	runManager->BeamOn(numEvents);
 
}

void
Geant4Simulation::
visualize(unsigned int nEvents, bool accumulate)
{
#ifdef G4VIS_USE
	// visualization manager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif
	
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/open HepRepFile");
    UI->ApplyCommand("/vis/drawVolume");
    UI->ApplyCommand("/vis/viewer/flush");
	
	if (nEvents > 0)
	{
	    UI->ApplyCommand("/vis/scene/add/trajectories");
	    UI->ApplyCommand("/vis/scene/add/hits");
		
		if (accumulate)
		{
			std::stringstream ss0;
			ss0 << "/vis/scene/endOfEventAction accumulate " << nEvents;
		    UI->ApplyCommand(ss0.str());
		}
		
		std::stringstream ss1;
		ss1 << "/run/beamOn " << nEvents;
	    UI->ApplyCommand(ss1.str());
	    //UI->ApplyCommand("/vis/reviewKeptEvents");
		
		
	}
}


} // namespace sim
} // namespace gex
