//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//


#ifndef GEX_UTIL_STR_HH
#define GEX_UTIL_STR_HH

#include <sstream>

namespace gex {
namespace util {

template<class... Args>
std::string
str(Args&&... args)
{
	std::stringstream ss;
	int unpack[]{(ss << args, 0)...};
	return ss.str();
}

} // namespace util 	
} // namespace gex 

#endif