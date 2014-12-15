//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_CHAIN_HH
#define GEX_UTIL_CHAIN_HH

namespace gex {
namespace util {

/// \class Chain
/// \brief A template pointer whose identity can be cycled.
///
/// Chain accepts a list of pointers. When dereferenced, it will return the current pointer in the list. When the advance() method is called, the next item in the list will become the current pointer. The chain will cycle back to the beginning when the end of the list is reached.
template <typename T>
class Chain : public T
{
public:

	Chain(std::vector<T*> vec)
	: chain(vec)
	{
		it = chain.begin();
		advance();
	}
	
	virtual ~Chain() {;}

	virtual T* operator-> ()
	{
		return *it;
	}
	
	virtual T& operator* ()
	{
		return **it;
	}
	
	virtual void advance()
	{
		it = (it!=chain.end) ? ++it : chain.begin();
	}
	
protected:
	T* current;
	std::vector<T*>::iterator it;
	std::vector<T*> chain;
};

} // namespace util 	
} // namespace gex 

#endif
