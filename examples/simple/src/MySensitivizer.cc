//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "MySensitivizer.hh"
#include <gex/create.hh>
#include <gex/sd/SDGroup.hh>
#include <gex/sd/EnergyDepSD.hh>
#include <gex/sd/TimeOfHitSD.hh>
#include <gex/sd/PrimaryVertexSD.hh>
#include <gex/ua/RootTreeManager.hh>
#include <gex/data/DataModuleGroup.hh>

MySensitivizer::
MySensitivizer(std::string f, std::string t, std::string b)
	: fileName(f), treeName(t), branchName(b)
{
	// do nothing else
}

void 
MySensitivizer::
makeSensitive(G4LogicalVolume* vol)
{
	using namespace gex;
	
	// We only want to make sensitive detectors for the worker threads.
	if (false == G4Threading::IsWorkerThread()) { return; }
	
	// --Set up our sensitive detectors. This is how we extract data from our simulation.
	//
	// Create an SDGroup and attach it to the volume.
	auto sdGroup = gex::sd::make_sensitive(vol, "sdGroup");
	
	// Create the job-specific sensitive detectors we want. In this case we are going to read out the total energy deposited in the volume, the time of the first interaction, and information about the original source particle. Note that PrimaryVertexSD is also a type of UserAction. The function gex::create handles its registration automagically.
	auto energy = gex::create<sd::EnergyDepSD>("energy");
	auto time = gex::create<sd::TimeOfHitSD>("time");
	auto primaryVertex = gex::create<sd::PrimaryVertexSD>("primaryVertex");
	
	// add the sensitive detectors to the group.
	sdGroup->add(energy).add(time).add(primaryVertex);
	
	
	// --Set up our DataModuleGroup. This is how we save the data from our simulation to disk.
	//
	// Get RootTreeManager for the ROOT file specified by fileName. The following lines of code will set up our simulation to write data to a TTree in this file. 
	auto rtm = ua::RootTreeManager::GetRootTreeManager(fileName);
	
	// Create the DataModuleGroup. Give it the sdGroup we want to read out and the name of the branch we want it to save data to in the TTree.
	auto dataGroup = data::make_readout(sdGroup,branchName);
	
	// choose the sensitive detectors from the sdGroup whose data you want to save.
	dataGroup->add(energy).add(time).add(primaryVertex);

	// Register the data group with the Root Tree Manager and give it the name of the tree we want to save the data in. **This line must be invoked AFTER selecting the sensitive detectors you want read out.**
	dataGroup->registerWith(rtm, treeName);
	
	// We have accomplished a few things:
	// 1) A separate TFile with a TTree containing the simulation data will be written for every thread for every run. As an example, the 3rd thread on the 2nd run will write to a file called fileName_run2_tr3.root which will contain a TTree called treeName with a branch called branchName.
	// 2) We have set up the TTree called treename to fill only for events where the sdGroup volume has a hit.
	// 3) We cause a ROOT dictionary library to be generated. We will need this to be able to read the data out later.
}






