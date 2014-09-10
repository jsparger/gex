#ifndef GETA_UA_USER_ACTION_MANAGER_HH
#define GETA_UA_USER_ACTION_MANAGER_HH

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserStackingAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"
#include <vector>
#include <memory>
#include <iostream>
#include "gex/ua/UserAction.hh"
#include "gex/ua/LifetimeExtension.hh"
#include "gex/util/make_unique.hh"

namespace gex {
namespace ua {

class EventActionGroup;
class RunActionGroup;
class StackingActionGroup;
class SteppingActionGroup;
class TrackingActionGroup;

/// \class UserActionManager
/// \brief A manager which will allow for more than one of each type of user action to be used with the G4RunManager. 
///
/// A manager which will allow for more than one of each type of user action to be used with the G4RunManager. This will allow for more modularized user actions and data recovery.

class UserActionManager
{
public:
	
	/// Get the thread local UserActionManager
	static UserActionManager* GetUserActionManager();
	
	/// Register a UserAction. 
	virtual void registerAction(UserAction* action);
	
	/// Register a UserAction and transfer ownership to UserActionManager
	virtual void registerAction(std::unique_ptr<UserAction> action);
	
	/// Register a run action for the master thread
	virtual void registerMasterRunAction(std::unique_ptr<G4UserRunAction> runAction); 
	
	/// Double dispatch function for UserAction registration
	virtual void addEventAction(G4UserEventAction* ea);
	
	/// Double dispatch function for UserAction registration
	virtual void addRunAction(G4UserRunAction* ra);
	
	/// Double dispatch function for UserAction registration
	virtual void addStackingAction(G4UserStackingAction* sa);
	
	/// Double dispatch function for UserAction registration
	virtual void addSteppingAction(G4UserSteppingAction* sa);
	
	/// Double dispatch function for UserAction registration
	virtual void addTrackingAction(G4UserTrackingAction* ta);
	
	/// Transfer ownership of a resource to the user action manager. Useful when a resource must exist for the life of the simulation.
	template <typename T>
	T* adopt(std::unique_ptr<T> obj)
	{
		T* rawPointer = obj.get();
		this->registerAction(std::make_unique<LifetimeExtension<T>>(std::move(obj)));
		return rawPointer;
	}
	
protected:
	/// Constructor. Use GetUserActionManager() to obtain an instance.
	UserActionManager();
	
	/// Destructor
	virtual ~UserActionManager() {;}

protected:
	std::vector<std::unique_ptr<UserAction>> actionVec;
	std::vector<std::unique_ptr<G4UserRunAction>> masterRunActionVec;
	EventActionGroup* eventGroup;
	RunActionGroup* runGroup;
	StackingActionGroup* stackGroup;
	SteppingActionGroup* stepGroup;
	TrackingActionGroup* trackingGroup;
	thread_local static std::unique_ptr<UserActionManager> theInstance;
	friend std::unique_ptr<UserActionManager>::deleter_type;
};

// These are classes for use only by UserActionManager. They hold the modular
// user actions and call them one by one when a method is invoked by the 
// G4RunManager.

/// \class EventActionGroup
/// \brief Utility class for UserActionManager.
class EventActionGroup : public G4UserEventAction
{
private:
	friend class UserActionManager;
	typedef std::vector<G4UserEventAction*> UserActionVec;
	UserActionVec actionList;
	EventActionGroup(){;}
public:
	void BeginOfEventAction(const G4Event* event) override;
	void EndOfEventAction(const G4Event* event) override;
};


/// \class RunActionGroup
/// \brief Utility class for UserActionManager.
class RunActionGroup : public G4UserRunAction
{
private:
	friend class UserActionManager;
	typedef std::vector<G4UserRunAction*> UserActionVec;
	UserActionVec actionList;
	RunActionGroup(){;}
public:
	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run* run) override;
	void EndOfRunAction(const G4Run* run) override;
};

/// \class StackingActionGroup
/// \brief Utility class for UserActionManager.
class StackingActionGroup : public G4UserStackingAction
{
private:
	friend class UserActionManager;
	typedef std::vector<G4UserStackingAction*> UserActionVec;
	UserActionVec actionList;
	StackingActionGroup(){;}
public:
	G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* track) override;
	void NewStage() override;
	void PrepareNewEvent() override;
};

/// \class SteppingActionGroup
/// \brief Utility class for UserActionManager.
class SteppingActionGroup : public G4UserSteppingAction
{
private:
	friend class UserActionManager;
	typedef std::vector<G4UserSteppingAction*> UserActionVec;
	UserActionVec actionList;
	SteppingActionGroup(){;}
public:
	void UserSteppingAction(const G4Step*) override;
	
};

/// \class TrackingActionGroup
/// \brief Utility class for UserActionManager.
class TrackingActionGroup : public G4UserTrackingAction
{
private:
	friend class UserActionManager;
	typedef std::vector<G4UserTrackingAction*> UserActionVec;
	UserActionVec actionList;
	TrackingActionGroup(){;}
public:
	void PreUserTrackingAction(const G4Track*) override;
	void PostUserTrackingAction(const G4Track*) override;
};

} // namespace ua
} // namespace gex

#endif
