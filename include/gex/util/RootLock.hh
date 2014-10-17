//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_ROOTLOCK_HH
#define GEX_UTIL_ROOTLOCK_HH 

#include <mutex>

namespace gex {
namespace util {

/// \class RootLock
/// \brief A class with a static mutex to handle Cern ROOT access.	
struct RootLock
{
	/// Lock this mutex before performing any non-threadsafe operations with ROOT. Most ROOT operations are not threadsafe, even those which the ROOT documentation claims to be.
	static std::mutex MUTEX;
};
	
	
} // namespace util 
} // namespace gex 

#endif
