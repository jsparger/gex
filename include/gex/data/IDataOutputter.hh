//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_IDATAOUTPUTTER_HH
#define GEX_DATA_IDATAOUTPUTTER_HH

#include <string>

namespace gex {

namespace ua {
	class RootTreeManager;
} // namespace ua
	
namespace data {

/// \class Abstract base class for classes which would like to register data with a RootTreeManager.
/// \brief  
///
///
struct IDataOutputter
{
	virtual void registerWith(ua::RootTreeManager* rtm, std::string treeName) = 0;
};
	
} // namespace data 	
} // namespace gex 

#endif
