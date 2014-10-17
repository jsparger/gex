//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UA_RUNDATAREGISTRATION_HH
#define GEX_UA_RUNDATAREGISTRATION_HH

#include "G4UserRunAction.hh"
#include "gex/ua/UserAction.hh"
#include "gex/ua/RootTreeManager.hh"
#include "gex/ua/UserActionManager.hh"
#include <string>

namespace gex {
namespace ua {

/// \class RunDataRegistration
/// \brief A class which will automatically register data with a RootTreeManager at the beginning of every Run.
///
/// RunDataRegistration will register a branch with a RootTreeManager at the beginning of every run. This is useful when the simulation will persist for multiple runs but will output the same data each time.
template <typename T>
class RunDataRegistration : public G4UserRunAction, public UserAction
{
public:
	/// Constructor. Takes a RootTreeManager \p rtm, a string \p tree representing the name of the tree to create the branch in, a string \p dataName representing the name of the data (which will be the name of the branch), and a pointer to the data used to fill the branch, \p d.
	RunDataRegistration(RootTreeManager* rtm, std::string tree, std::string dataName, T* d)
		: rootTreeManager(rtm), treeName(tree), branchName(dataName), data(d)
	{
		// do nothing else
	}
	
	virtual ~RunDataRegistration() {;}
	
	virtual void registerWith(UserActionManager* uam) override
	{
		uam->addRunAction(this);
	}
	
	virtual void BeginOfRunAction(const G4Run*) override
	{
		rootTreeManager->registerData(treeName, branchName, data);
	}
	
protected:
	RootTreeManager* rootTreeManager;
	std::string treeName, branchName;
	T* data;
};
	
} // namespace ua 
} // namespace gex 

#endif
