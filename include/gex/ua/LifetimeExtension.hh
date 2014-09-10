//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UA_LIFETIME_EXTENSION_HH
#define GEX_UA_LIFETIME_EXTENSION_HH

#include "gex/ua/UserAction.hh"
#include <memory>

namespace gex {
namespace ua {

/// \class LifetimeExtension
/// \brief UserAction for tying the lifetime of an object to the lifetime of the simulation.
///
/// LifetimeExtension is a special UserAction designed to tie the lifetime of an object to the lifetime of the simulation by transfering ownership to the UserActionManager. The user does not need to wrap the object himself. Simply calling UserActionManager::adopt() is sufficient.
	
template <typename T>
class LifetimeExtension : public UserAction
{
public:
	/// Constructor for std::unique_ptr
	LifetimeExtension(std::unique_ptr<T> data)
		: uniqueData(std::move(data))
	{
		// do nothing else
	}
	
	/// Constructor for std::shared_ptr
	LifetimeExtension(std::shared_ptr<T> data)
		: sharedData(std::move(data))
	{
		// do nothing else
	}
	
	virtual ~LifetimeExtension() {;}
	
	/// Does nothing in this case.
	virtual void registerWith(UserActionManager*) override 
	{
		// do nothing
	}
	
protected:
	std::unique_ptr<T> uniqueData;
	std::shared_ptr<T> sharedData;
};
	
} // namespace ua
} // namespace gex

#endif
