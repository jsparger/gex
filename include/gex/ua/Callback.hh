//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UA_CALLBACK_HH
#define GEX_UA_CALLBACK_HH 

#include "UserAction.hh"
#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserStackingAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"
#include "UserActionManager.hh"
#include <functional>
#include <set>

namespace gex {
namespace ua {

/// \enum Cycle
/// \brief Enum indicating Geant4 user hooks. These correspond exactly to the virtual methods of the various G4User*Action classes.
enum class Cycle
{
	EVENT_BEGIN, 	///< Called by Geant4 at the beginning of an Event.
	EVENT_END, 		///< Called by Geant4 at the end of an Event.
	RUN_BEGIN, 		///< Called by Geant4 at the beginning of a Run.
	RUN_END,  		///< Called by Geant4 at the end of a Run.
	STACK_EVENT,	///< Called by Geant4 when preparing a new event.
	STACK_STAGE,	///< Called by Geant4 when preparing a new stage.
	STACK_TRACK,  	///< Called by Geant4 when classifying a new Track.
	STEP, 			///< Called by Geant4 during each Step.
	TRACK_PRE, 		///< Called by Geant4 before tracking.
	TRACK_POST		///< Called by Geant4 after tracking.
};

/// \class Callback
/// \brief A UserAction which can execute an arbitrary function at any place during the simulation where Geant4 exposes a user action hook.
///
/// Callback accepts a std::function with no return arguments which it will execute at the simulation cycle locations specified by the user. This class works by registering itself with the UserActionManager as the type of G4UserActions needed to trigger at the selected cycle locations.
class Callback : 	public UserAction, public G4UserEventAction, public G4UserRunAction, 
				  	public G4UserStackingAction, public G4UserSteppingAction, 
					public G4UserTrackingAction
{
public:
	/// Constructor. Provide a no-arg, no return callback function \p func and a set of simulation cycle times at which this callback should be executed.
	Callback(std::function<void()> func, std::set<Cycle> initCycle);
	
	virtual ~Callback() {;}
	
	virtual void registerWith(UserActionManager* uam) override;
	
	virtual void BeginOfEventAction(const G4Event*) override;
	virtual void EndOfEventAction(const G4Event*) override;
	virtual void BeginOfRunAction(const G4Run*) override;
	virtual void EndOfRunAction(const G4Run*) override;
	virtual void NewStage() override;
	virtual void PrepareNewEvent() override;
	virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* track) override;
	virtual void UserSteppingAction(const G4Step*) override;
	virtual void PreUserTrackingAction(const G4Track*) override;
	virtual void PostUserTrackingAction(const G4Track*) override;
	
protected:
	std::function<void()> theCallback;
	std::set<Cycle> cycleSet;
	bool isEventAction, isRunAction, isStackingAction, isSteppingAction, isTrackingAction;
	bool doEventBegin, doEventEnd, doRunBegin, doRunEnd, doStackStage, doStackEvent, doStackTrack, doTrackPre, doTrackPost;
};
	
} // namespace ua 
} // namespace gex 

#endif
