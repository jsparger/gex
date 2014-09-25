//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_USER_INFO_ACCESS_HH
#define GEX_DATA_USER_INFO_ACCESS_HH

#include "gex/data/NamedData.hh"
#include "G4VUserTrackInformation.hh"
#include <utility>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace gex {
namespace data {

// a helper class for UserInfoAccess	
template <class T>	
struct UserInfoWrapper : public T
{
	virtual ~UserInfoWrapper() {;}
	virtual void Print() const override {;}
	std::unique_ptr<NamedData> data;
};

// UserInfoWrapper specialization for G4VUserTrackInformation which has a name for some reason.
template <>
struct UserInfoWrapper<G4VUserTrackInformation> : public G4VUserTrackInformation
{
	UserInfoWrapper() : G4VUserTrackInformation("gex::data::UserInfo") {;}
	virtual ~UserInfoWrapper() {;}
	virtual void Print() const override {;}
	std::unique_ptr<NamedData> data;
};

/// \class UserInfoAccess
/// \brief Allows a NamedData to be attached to or read from any Geant4 class which allows user information to be stored with it.
///
///	Allows a NamedData to be attached to or read from any Geant4 class which allows user information to be stored and retrieved via G4Type::SetUserInformation() and G4Type::GetUserInformation respectively. An example might be G4UserTrackingInformation which can be stored in a G4Track. Using UserInfoAccess, this data may be stored or retrieved in a G4Track. The same data may also be relocated easily to another object such as a G4Step.
template <class G4Type>
struct UserInfoAccess
{
	typedef decltype(std::declval<G4Type>().GetUserInformation()) G4InfoPointerType;
	typedef typename std::remove_pointer<G4InfoPointerType>::type G4InfoType;
	
	/// Checks to see if a G4Type object has user information attached to it. It does not check to make sure the user info is of the type needed by this class.
	virtual bool hasData(const G4Type* g4obj)
	{
		return (nullptr != g4obj->GetUserInformation());
	}
	
	/// Retrieves the NamedData from the G4Type object. Throws an error if there is no user data or the user data is of the wrong type.
	virtual NamedData* get(const G4Type* g4obj)
	{
		auto* wrapper = dynamic_cast<UserInfoWrapper<G4InfoType>*>(g4obj->GetUserInformation());
		if (nullptr == wrapper)
		{
			throwWrongTypeError(); // TODO: translate this into error.
		}
		else
		{
			return wrapper->data.get();
		}
	}
	
	/// Attaches the NamedData \p data  as user data in the G4Type \p g4obj. Caution: overwriting existing user data without deleting it will cause a memory leak! You can check if data already exists using hasData().
	virtual void set(G4Type* g4obj, std::unique_ptr<NamedData> data)
	{
		auto* wrapper = new UserInfoWrapper<G4InfoType>();
		wrapper->data = std::move(data);
		g4obj->SetUserInformation(wrapper);
	}


protected:

	void throwWrongTypeError()
	{
		std::stringstream ss;
		ss  << "UserInfoAccess::get(...): Error! UserInfo was either null not of expected type. "
			<< "Check for null first with UserInfoAccess::hasData(...). If this return true, "
			<< "have you added an incompatible G4UserInformation to this object somewhere else?";
		throw(std::runtime_error(ss.str()));
	}

};
	
} // namespace data 
} // namespace gex 

#endif
