//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/ua/Callback.hh"

namespace gex {
namespace ua {

Callback::
Callback(std::function<void()> func, std::set<Cycle> initCycle)
	: 	theCallback(func), cycleSet(initCycle), 
		isEventAction(false), isRunAction(false), isStackingAction(false), isSteppingAction(false), isTrackingAction(false),
		doEventBegin(false), doEventEnd(false), doRunBegin(false), doRunEnd(false), doStackStage(false), doStackEvent(false), 
		doStackTrack(false), doTrackPre(false), doTrackPost(false)
		{
			// do nothing else
		}

void 
Callback::
registerWith(UserActionManager* uam)
{
	// TODO: couldn't this be moved to constructor?
	for (const auto& cycle : cycleSet)
	{	
		if (Cycle::EVENT_BEGIN == cycle) 		{ isEventAction = true; 	doEventBegin = true;	}
		else if (Cycle::EVENT_END == cycle) 	{ isEventAction = true; 	doEventEnd = true;		}
		else if (Cycle::RUN_BEGIN == cycle) 	{ isRunAction = true; 		doRunBegin = true; 		}
		else if (Cycle::RUN_END == cycle) 		{ isRunAction = true; 		doRunEnd = true;		}
		else if (Cycle::STACK_EVENT == cycle) 	{ isStackingAction = true; 	doStackEvent = true; 	}
		else if (Cycle::STACK_STAGE == cycle) 	{ isStackingAction = true; 	doStackStage = true; 	}
		else if (Cycle::STACK_TRACK == cycle) 	{ isStackingAction = true; 	doStackTrack = true; 	}
		else if (Cycle::STEP == cycle) 			{ isSteppingAction = true; 	/*no need*/				}
		else if (Cycle::TRACK_PRE == cycle) 	{ isTrackingAction = true; 	doTrackPre = true; 		}
		else if (Cycle::TRACK_POST == cycle) 	{ isTrackingAction = true; 	doTrackPost = true; 	}
	}
	
	if (isEventAction) 			{ uam->addEventAction(this); 	}
	else if (isRunAction) 		{ uam->addRunAction(this); 		}
	else if (isStackingAction) 	{ uam->addStackingAction(this); }
	else if (isSteppingAction) 	{ uam->addSteppingAction(this); }
	else if (isTrackingAction) 	{ uam->addTrackingAction(this); }
}

void 
Callback::
BeginOfEventAction(const G4Event*) 
{
	if (doEventBegin) theCallback();
}

void 
Callback::
EndOfEventAction(const G4Event*) 
{
	if (doEventEnd) theCallback();
}

void 
Callback::
BeginOfRunAction(const G4Run*) 
{
	if (doRunBegin) theCallback();
}

void 
Callback::
EndOfRunAction(const G4Run*) 
{
	if (doRunEnd) theCallback();
}

void 
Callback::
NewStage() 
{
	if (doStackStage) theCallback();
}

void 
Callback::
PrepareNewEvent()
{
	if (doStackEvent) theCallback();
}

G4ClassificationOfNewTrack 
Callback::
ClassifyNewTrack(const G4Track* track)
{
	if (doStackTrack) theCallback();
	return G4UserStackingAction::ClassifyNewTrack(track);
}

void 
Callback::
UserSteppingAction(const G4Step*) 
{
	// No need to check. Only one stepping action method.
	theCallback();
}

void 
Callback::
PreUserTrackingAction(const G4Track*) 
{
	if (doTrackPre) theCallback();
}

void 
Callback::
PostUserTrackingAction(const G4Track*)
{
	if (doTrackPost) theCallback();
}

} // namespace ua 
} // namespace gex 
