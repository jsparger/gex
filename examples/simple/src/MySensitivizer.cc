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

MySensitivizer::
MySensitivizer(const std::string fileName, const std::string treeName)
{
	// TODO: implement
}

void 
MySensitivizer::
makeSensitive(G4LogicalVolume* vol)
{
	using namespace gex;
	
	// We only want to make sensitive detectors for the worker threads.
	if (false == G4Threading::IsWorkerThread()) { return; }
	
	// --Set up our sensitive detectors. This is how we get data from our simulation.
	
	// Create an SDGroup and attach it to the volume. We don't use gex::create in this special case because we need to let Geant4 handle memory management.
	auto sdGroup = gex::sd::make_sensitive(vol);
	
	// Create the job-specific sensitive detectors we want. In this case we are going to read out the total energy deposited in the volume, the time of the first interaction, and information about the original source particle. Note that PrimaryVertexSD is also a type of UserAction. The function ua::create handles its registration automagically.
	auto energy = gex::create<sd::EnergyDepSD>("energy");
	auto time = gex::create<sd::TimeOfHitSD>("time");
	auto primaryVertex = gex::create<sd::PrimaryVertexSD>("primaryVertex");
	
	// add the sensitive detectors to the group.
	sdGroup->add(energy).add(time).add(primaryVertex);
	
	
	// --Set up our DataModuleGroup. This is how we save the data from our simulation to disk.
	
	// Create the DataModuleGroup. 
	auto dataGroup = gex::create<data::DataModuleGroup>("dataGroup");
	
	// choose the sensitive detectors whose data you want to save.
	dataGroup->add(energy).add(time).add(primaryVertex);
	
	// get RootTreeManager for the ROOT file specified by fileName.
	auto rtm = ua::RootTreeManager::GetRootTreeManager(fileName);
	
	// register the data group with the Root Tree Manager and give it the name of the tree we want to save the data in. Also tell the sdGroup to update the dataGroup.  This will do a few things:
	// 1) cause a TFile with a TTree containing the data to be written for every run.
	// 2) cause the TTree specified by treeName to only be filled for events where the volume has a hit.
	// 3) cause a ROOT dictionary library to be generated.
	dataGroup->registerWith(rtm, treeName);
	sdGroup->inform(dataGroup);
	
	// TODO: write a function like this:
	// std::string name = gex::util::str(3,"dog","america",5);
	
	// generate a callback that will be invoked at the beginning of every event to reset the
	// dataGroup.
	gex::create<ua::Callback>([dataGroup]{dataGroup->reset();}, {ua::Cycle::EVENT_BEGIN}));
	
	++sdnum;
}






