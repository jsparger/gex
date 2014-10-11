//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_CREATE_HH
#define GEX_CREATE_HH

#include "gex/ua/UserActionManager.hh"

/// The gex namespace
namespace gex {
	
/// @cond
	
/// \brief Creates an object of type T that will live for the lifetime of the simulation. Returns a pointer to the object. Invoked for non-UserAction types.
template<class T, class... Args, typename std::enable_if<!std::is_base_of<UserAction, T>::value, int>::type = 0>
T*
create_helper(Args&&... args) 
{
	auto uam = UserActionManager::GetUserActionManager();
    return uam->adopt(std::make_unique<T>(std::forward<Args>(args)...));
}

/// Creates, transfers ownership to, and registers a UserAction with the UserActionManager. Returns a pointer to the UserAction. Invoked for UserAction types.
template<class T, class... Args, typename std::enable_if<std::is_base_of<UserAction, T>::value, int>::type = 0>
T*
create_helper(Args&&... args)
{
	auto uam = UserActionManager::GetUserActionManager();
    return uam->registerAction(std::make_unique<T>(std::forward<Args>(args)...));
}

/// @endcond

/// \brief Creates an object of type T that will live for the duration of the simulation. Magically handles the setup of gex types within the framework.
template<class T, class... Args>
T*
create(Args&&... args)
{
	return create_helper<T>(std::forward<Args>(args)...);
}



} // namespace gex 

#endif