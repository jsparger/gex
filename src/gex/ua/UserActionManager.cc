//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/ua/UserActionManager.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"

namespace gex {
namespace ua {

thread_local UserActionManager* UserActionManager::theInstance = nullptr;

UserActionManager*
UserActionManager::
GetUserActionManager()
{
	if (nullptr == theInstance)
	{
		theInstance = new UserActionManager();
	}
	
	//return theInstance.get();
	return theInstance;
}

UserActionManager::
UserActionManager()
: 	eventGroup(nullptr), runGroup(nullptr),
	stackGroup(nullptr), stepGroup(nullptr),
	trackingGroup(nullptr)
{
	// TODO: review this...
	// This could fix a future bug...
	// Only UserRunActions are allowed in the case of the Master Thread.
	if (G4Threading::IsWorkerThread()) {
		eventGroup = new EventActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(eventGroup); 
		stackGroup = new StackingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(stackGroup);
		stepGroup = new SteppingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(stepGroup);
		trackingGroup = new TrackingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(trackingGroup);  
	}
	runGroup = new RunActionGroup();
	G4RunManager::GetRunManager()->SetUserAction(runGroup);
}

void
UserActionManager::
registerAction(UserAction* action)
{
	action->registerWith(this);
}

void
UserActionManager::
registerAction(std::unique_ptr<UserAction> action)
{
	action->registerWith(this);
	actionVec.push_back(std::move(action));
}

void
UserActionManager::
registerMasterRunAction(std::unique_ptr<G4UserRunAction> runAction)
{
	addRunAction(runAction.get());
	masterRunActionVec.push_back(std::move(runAction));
}

void
UserActionManager::
addEventAction(G4UserEventAction* action)
{
	if (!eventGroup)
	{ 
		eventGroup = new EventActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(eventGroup); 
	}
	
	eventGroup->actionList.push_back(action);	
}

void
UserActionManager::
addRunAction(G4UserRunAction* action)
{
	if (!runGroup)
	{ 
		runGroup = new RunActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(runGroup); 
	}
	
	runGroup->actionList.push_back(action);	
}

void
UserActionManager::
addStackingAction(G4UserStackingAction* action)
{
	if (!stackGroup)
	{ 
		stackGroup = new StackingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(stackGroup); 
	}
	
	stackGroup->actionList.push_back(action);	
}

void
UserActionManager::
addSteppingAction(G4UserSteppingAction* action)
{
	if (!stepGroup)
	{ 
		stepGroup = new SteppingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(stepGroup); 
	}
	
	stepGroup->actionList.push_back(action);	
}

void
UserActionManager::
addTrackingAction(G4UserTrackingAction* action )
{
	if (!trackingGroup)
	{ 
		trackingGroup = new TrackingActionGroup();
		G4RunManager::GetRunManager()->SetUserAction(trackingGroup); 
	}
	
	trackingGroup->actionList.push_back(action);	
}

void
EventActionGroup::
BeginOfEventAction(const G4Event* arg)
{

	for (auto& action : actionList)
	{
		action->BeginOfEventAction(arg);

	}
}


void
EventActionGroup::
EndOfEventAction(const G4Event* arg)
{
	for (auto& action : actionList)
	{
		action->EndOfEventAction(arg);
	}
}

G4Run*
RunActionGroup::
GenerateRun()
{
	// this doesn't make sense because it has a return value.
	// only return the first.
	if (actionList.size() > 0)
	{
		return actionList[0]->GenerateRun();
	}
	else
	{
		return G4UserRunAction::GenerateRun();
	}
	
}

void
RunActionGroup::
BeginOfRunAction(const G4Run* arg)
{

	for (auto& action : actionList)
	{
		action->BeginOfRunAction(arg);
	}

}

void
RunActionGroup::
EndOfRunAction(const G4Run* arg)
{
	for (auto& action : actionList)
	{
		action->EndOfRunAction(arg);
	}
}


G4ClassificationOfNewTrack
StackingActionGroup::
ClassifyNewTrack(const G4Track* arg)
{
	// this doesn't make sense because it has a return value.
	// only return the first.
	if (actionList.size() > 0)
	{
		return actionList[0]->ClassifyNewTrack(arg);
	}
	else
	{
		return G4UserStackingAction::ClassifyNewTrack(arg);
	}
		
}


void
StackingActionGroup::
NewStage()
{
	for (auto& action : actionList)
	{
		action->NewStage();
	}
}


void
StackingActionGroup::
PrepareNewEvent()
{
	for (auto& action : actionList)
	{
		action->PrepareNewEvent();
	}
}


void
SteppingActionGroup::
UserSteppingAction(const G4Step* arg)
{
	for (auto& action : actionList)
	{
		action->UserSteppingAction(arg);
	}
}



void
TrackingActionGroup::
PreUserTrackingAction(const G4Track* arg)
{
	for (auto& action : actionList)
	{
		action->PreUserTrackingAction(arg);
	}
}


void
TrackingActionGroup::
PostUserTrackingAction( const G4Track* arg)
{
	for (auto& action : actionList)
	{
		action->PostUserTrackingAction(arg);
	}
}

} // namespace ua
} // namespace gex
