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

/// The util namespace
namespace util {

/// \brief Converts arguments to strings using std::stringstream and concatenates them.
///
/// Example usage:
/// \code{.cpp}
/// std::cout << gex::util::str("std::stringstream takes ", 3, "lines, but this takes just", 1, "!") << "\n";
/// \endcode
template<class... Args>
std::string
str(Args&&... args)
{
	// For me later wondering how this works, see http://en.cppreference.com/w/cpp/language/parameter_pack and look at "Braced init lists". You can use them to call a function on each element of a parameter pack in order. The expression (ss << args, 0) works as a result of the comma operator (who knew?). 
	// Example 1: a = b, c;    // a is set to the value of b!
	// Example 2: a = (b, c);  // a is set to the value of c!
	// Read about it here: http://stackoverflow.com/questions/54142/how-does-the-comma-operator-work
	std::stringstream ss;
	int unpack[]{(ss << args, 0)...};
	(void)unpack; // to prevent unused variable warning. (I sure hope this prevents optimization too.)
	return ss.str();
}

} // namespace util 	
} // namespace gex 

#endif