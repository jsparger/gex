#ifndef GETA_UA_USER_ACTION_HH
#define GETA_UA_USER_ACTION_HH

namespace gex {
namespace ua {
	
class UserActionManager;

/// \class UserAction
/// \brief Abstract base class for all UserActions
///
/// This class is the abstract base class for all UserActions. When a user wants to create a new UserAction (such as a G4UserSteppingAction or G4UserTrackingAction), the user should inherit from this class and use the registerWith function to call the appropriate registration functions in the UserActionManager.
class UserAction
{
public:
	/// Destructor
	virtual ~UserAction() {;}
	/// This method will be called by the UserActionManager when the UserAction is registered with it. The user should call the appropriate registration functions on the UserActionManager \p ua and pass the "this" parameter.
	virtual void registerWith(UserActionManager* ua) = 0;
};

} // namespace ua 
} // namespace gex

#endif
