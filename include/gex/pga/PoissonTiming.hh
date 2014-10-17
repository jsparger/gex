//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_POISSON_TIMING
#define GEX_PGA_POISSON_TIMING 

#include "gex/pga/TimeDistribution.hh"
#include "Math/Random.h"

namespace gex {
namespace pga {

/// \class PoissonTiming
/// \brief A TimeDistribution for Poisson processes.
///
/// PoissonTiming will sample from an exponential distribution appropriate for a Poisson process with a given mean time between decays.
class PoissonTiming : public TimeDistribution
{
public:
	/// Constructor. Takes the mean time between events, or 1/eventRate.
	PoissonTiming(double mean);
	virtual ~PoissonTiming() {;}
	virtual double getTime(unsigned int n = 1, G4Event* event = nullptr) override;
protected:
	double mean;
	ROOT::Math::RandomMT random;
};
	
} // namespace pga 	
} // namespace gex 

#endif
