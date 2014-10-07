//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//


#ifndef GEX_UTIL_TSACCUMULATOR_HH
#define GEX_UTIL_TSACCUMULATOR_HH

#include <mutex>

namespace gex {
namespace util {

/// \class TSAccumulator
/// \brief A thread safe accumulator.
///	
/// TSAccumulator is a thread safe accumulator. One application for this class is to create a clock that can be used to synchronize events across threads. Another example is a position updated via deltas from different threads. 
template <typename T>
class TSAccumulator
{
public:
	/// Constructor
	TSAccumulator(T init)
	: 	value(initialValue), initialValue(init)
	{
		// do nothing else
	}
	
	/// Get the current value
	T getValue()
	{
		std::lock_guard<std::mutex> lock(valueMutex);
		return value;
	}
	
	/// Accumulate the value incr into the value. Return the new value.
	T accumulate(T incr)
	{
		std::lock_guard<std::mutex> lock(valueMutex);
		value += incr;
		return value;
	}
	
	/// Reset to the initial value.
	void reset()
	{
		std::lock_guard<std::mutex> lock(valueMutex);
		value = initialValue;
	}
	
private:
	T value;
	T initialValue;
	std::mutex valueMutex;
};

} // namespace util
} // namespace gex

#endif
