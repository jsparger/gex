//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_TIME_DISTRIBUTION_HH
#define GEX_PGA_TIME_DISTRIBUTION_HH 

class G4Event;

namespace gex {
namespace pga {

/// \class TimeDistribution
/// \brief Abstract base class for timing distributions.
class TimeDistribution
{
public:
	virtual ~TimeDistribution () {;}
	
	// TODO: n parameter is a hack to allow for motion and vetoed events. This functionality should be added in a less intrusive way.
	/// Sample a time. Get the time after \p n samples. 
	virtual double getTime(unsigned int n = 1, G4Event* event = nullptr) = 0;
};
	
} // namespace pga 	
} // namespace gex 

#endif
