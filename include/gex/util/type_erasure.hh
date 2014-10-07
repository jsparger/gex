//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_TYPE_ERASURE_HH
#define GEX_UTIL_TYPE_ERASURE_HH

#include <typeinfo>
#include <stdexcept>

namespace gex {
namespace util {

// A wrapper around dynamic cast modeled after boost::any_cast
// TODO: what error checking should be done at the point of cast?	
template <class T>
struct dynamic_cast_wrapper
{
    class bad_dynamic_cast : public std::bad_cast
    {
    public:
        virtual const char * what() const throw()
        {
            return "gex::util::dynamic_cast_wrapper::bad_dynamic_cast: "
                   "failed conversion using dynamic_cast";
        }
    };
	
	template <class U>
	static U* cast(T* t)
	{
		return dynamic_cast<U*>(t);
	}
	
	// template <class U>
	// static const U* cast(const T* t)
	// {
	// 	return dynamic_cast<U*>(t);;
	// }
	// 
	// template <class U>
	// static U cast(T& t)
	// {
	// 	typedef typename std::remove_reference<U>::type nonref;
	// 	nonref* result = cast<nonref>(&t);
	// 	if (!result) 
	// 		{ throw bad_dynamic_cast(); }
	// 	return *result;
	// }
	// 
	// template <class U>
	// static U cast(const T& t)
	// {
	// 	typedef typename std::remove_reference<U>::type nonref;
	// 	return cast<const nonref&>(const_cast<T&>(t));
	// }
};

template <class T>
struct no_package
{
	static T pack(T t)
	{
		return t;
	}
	
	static T& unpack(T& t)
	{
		return t;
	}
};

template <template<class> class SmartType, class T>
struct smart_ptr_packager
{
	static SmartType<T> pack(T* val)
	{
		return std::move(SmartType<T>(val));
	}
	
	static T* unpack(SmartType<T>& val)
	{
		return val.get();
	}
	
	static T* unpack(const SmartType<T>& val)
	{
		return val.get();
	}
};
	
template <	class Container,
	 		class Packager = no_package<typename Container::mapped_type>, 
			class Caster = dynamic_cast_wrapper<typename Container::mapped_type>	>
class type_erased_map_wrapper
{
public:
	typedef Container container_type;
	typedef Packager packager_type;
	typedef Caster caster_type;
	
	container_type store;
};
	
} // namespace util 
} // namespace gex 

#endif
