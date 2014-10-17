//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/PoissonTiming.hh"
#include "Randomize.hh"

namespace gex {
namespace pga {
	
PoissonTiming::
PoissonTiming(double m)
	: mean(m)
{
	random.SetSeed(time(nullptr));
}

double
PoissonTiming::
getTime(unsigned int n, G4Event*)
{
	if (1 == n)
	{
		return G4RandExponential::shoot(mean);
	}
	else
	{
		return random.Gamma(n,mean);
	}
}
	
} // namespace pga 	
} // namespace gex 
