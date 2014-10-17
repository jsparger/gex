//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SIM_GEANT4SIMULATION_HH
#define GEX_SIM_GEANT4SIMULATION_HH

#include <memory>

class G4RunManager;
class G4VUserActionInitialization;
class G4VUserPhysicsList;
class G4VUserDetectorConstruction;

namespace gex {
namespace sim {

/// \class Geant4Simulation
/// \brief A helper to set up and run a Geant4 simulation
///
/// Geant4Simulation helps set up a simulation in Geant4. It allows the user to choose between single and multithreaded execution. The user may set a user action initialization, physics list, and detector construction. If these are not supplied, default (dummy) values are used. This class can also generate HepRep visualizations. 
class Geant4Simulation
{
public:
	/// Constructor. Choose whether to use the multithreaded Geant4 tools and select the number of threads.
	Geant4Simulation(bool isMultiThreaded = false, unsigned int numThreads = 1);
	
	/// Destructor
	virtual ~Geant4Simulation();
	
	/// Set a user action initialization for the simulation. DummyUserActionInitialization will be used if this method is not invoked. Returns the simulation for method chaining.
	Geant4Simulation& setUserActionInitialization(G4VUserActionInitialization* uai);
	
	/// Set a physics list for the simulation. The Geant4 built-in physics list QGSP_BIC will be used if this method is not invoked. Returns the simulation for method chaining.
	Geant4Simulation& setPhysicsList(G4VUserPhysicsList* phys);
	
	/// Set a detector construction for the simulation. DummyDetectorConstruction will be used if this method is not invoked. Returns the simulation for method chaining.
	Geant4Simulation& setDetectorConstruction(G4VUserDetectorConstruction* det);
	
	/// Set the number of events to simulate per run.
	Geant4Simulation& setNumberOfEvents(unsigned int numberOfEvents);
	
	/// Initialize the simulation. This method must be called before execute().
	virtual void initialize();
	
	/// Execute one run.
	virtual void execute();
	
	/// Generate HepRep visualization files for \p nEvents number of events. Set \p nEvents to zero if you only want to visualize the detector geometry. Set \p accumulate to true if you wish to see all events in the same visualization, or false if you want to visualize each event separately.
	virtual void visualize(unsigned int nEvents = 0, bool accumulate = false);
	
protected:
	std::unique_ptr<G4RunManager> runManager;
	bool useDefaultUserActionInitialization;
	bool useDefaultPhysics;
	bool useDefaultDetectorConstruction;
	G4VUserActionInitialization* userActionInitialization;
	G4VUserPhysicsList* physicsList;
	G4VUserDetectorConstruction* detectorConstruction;
	unsigned int numThreads;
	unsigned int numEvents;
};

} // namespace sim
} // namespace gex

#endif
