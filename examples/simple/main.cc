//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "TApplication.h"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "QGSP_BIC.hh"

#include <gex/sim/Geant4Simulation.hh>
#include <gex/geom/GeometryManager.hh>
#include <gex/geom/BoxWorld.hh>

#include "MyDetector.hh"
#include "MySensitivizer.hh"
#include "MyUserActionInitialization.hh"

int main()
{
	// TODO: maybe these initializations should be put in a helper function?
	// gex::sim::initialize(); // <-- maybe like this?
	//REQUIRED for some Cern ROOT things to work. So weird.
	TApplication theApp("theApp", 0, 0);
	// initialize random engine
	CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
	G4Random::setTheEngine( &defaultEngine );
	G4int seed = time( NULL );
	G4Random::setTheSeed( seed );

	// create a multithreaded simulation with 4 threads. This *must* be done first in a program to initialize Geant4.
	gex::sim::Geant4Simulation sim(true,4);

	// create a simulation clock with an initial time of 0 seconds.
	auto clock = std::make_unique<gex::util::TSAccumulator<double>>(0.0*s);

	// create our custom sensitivizer
	std::string fileName = "../output/simple";
	auto sens = new MySensitivizer(fileName,"tree","data");

	// Create our world volume.
	gex::geom::BoxWorld bw(300*m,50*m,100*m);
	G4VPhysicalVolume* world = bw.construct();

	// create a geometry manager. Give it our world volume and sensitivizer.
	// next, we add the geometry elements we want in our world volume. In this case we add a custom built detector and a custom built concrete slab.
	auto geometryManager = new gex::geom::GeometryManager(world,sens);
	geometryManager->addGeometry(std::make_unique<MyDetector>());

	// set up the simulation:
	// - let our geometry manager be the detector construction
	// - use Geant4's built in BGSP_BIC physics list.
	// - set up our custom user action initialization. It requires a filename and a simulation clock.
	// - set the number of events to 1 billion
	sim.setDetectorConstruction(geometryManager);
	sim.setPhysicsList(new QGSP_BIC());
	sim.setUserActionInitialization(new MyUserActionInitialization(fileName, std::move(clock)));
	sim.setNumberOfEvents(1e3);

	// initialize the simulation.
	sim.initialize();

	// Now let's run it! simulate 5 runs.
	// Each call to execute performs a run.
	unsigned int numRuns = 1;
	for (unsigned int i = 0; i < numRuns; ++i)
	{
		std::cout << "Run " << i << "/" << numRuns << "...";
		sim.execute();
		std::cout << "finished!\n";
	}

	// uncomment the line below to visualize 100 events
	sim.visualize(100,true);

	std::cout << "simulation complete!\n";
}