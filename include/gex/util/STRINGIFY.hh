//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//


#ifndef GEX_UTIL_STRINGIFY_HH
#define GEX_UTIL_STRINGIFY_HH

/// Macro to create turn an argument into a string literal.
#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

#endif
