//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_ACCESS
#define GEX_UTIL_ACCESS

#include <utility>
#include "gex/data/NamedData.hh"
#include "gex/util/type_erasure.hh"

namespace gex {


namespace util {
	
namespace te {	
	
	/// \class Access
	/// \brief A template class which abstracts access to type erased containers 
	///
	/// Access allows a user to access the contents and write to a type erased container without knowing the details of its implementation. Get an Access for a container using get_access().
	template <class Container, class Definitions>
	class Access
	{
	public:
		typedef typename Definitions::caster_type caster;
		typedef typename Definitions::packager_type packager;
		
		/// Constructor. Requires a type erased container, \p c, to access.
		Access(Container& container) : c(&container) {;}
	
		/// Returns a pointer to the content in the type erased container given by the key, \p k. The key type is detemined by the container.
		template <class T>
		T* get(const typename Definitions::container_type::key_type& k)
		{
			T* item = nullptr;
			auto it = c->store.find(k);
			if (it != c->store.end())
			{ 
				item = caster::template cast<T>(packager::unpack(it->second));
			}
	
			return item;
		}
	
		/// Inserts an value of type T into the container, associating it with the key \p k. Depending on the container type, the container may take ownership of the pointer, copy it, or perform some other operation.
		template <typename T>
		bool insert(const typename Definitions::container_type::key_type& k, T* value)
		{
			return c->store.emplace(k,std::move(packager::pack(value))).second;
		}
	
	private:
		Container* c;
	};

	/// @cond
	template <class Container>
	struct Definitions
	{
		typedef typename Container::container_type container_type;
		typedef typename Container::caster_type caster_type;
		typedef typename Container::packager_type packager_type;
	};

	template <>
	struct Definitions<gex::data::NamedData>
	{
		typedef typename std::map<std::string, gex::util::value_ptr<gex::data::IData>> container_type;
		typedef typename gex::util::dynamic_cast_wrapper<data::IData> caster_type;
		typedef typename gex::util::smart_ptr_packager<value_ptr, data::IData> packager_type;
	};
	
	template <>
	struct Definitions<const gex::data::NamedData>
	{
		typedef typename std::map<std::string, gex::util::value_ptr<gex::data::IData>> container_type;
		typedef typename gex::util::dynamic_cast_wrapper<data::IData> caster_type;
		typedef typename gex::util::smart_ptr_packager<value_ptr, data::IData> packager_type;
	};
	/// @endcond
			
} // namespace te

/// \relates te::Access
/// \brief Get the access for a type erased container
///
/// Use this function to get an Access for a type erased associative container.
/// 
/// Example usage:
/// \code{.cpp}
/// auto access = gex::util::get_access(myContainer);
/// \endcode
template<class Container>
te::Access<Container, te::Definitions<Container>>
get_access(Container& c)
{
	return te::Access<Container, te::Definitions<Container>>(c);
}

	
} // namespace util 
} // namespace gex 

#endif
