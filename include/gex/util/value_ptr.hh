//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_UTIL_VALUE_PTR_HH
#define GEX_UTIL_VALUE_PTR_HH

namespace gex {
namespace util {

/// \class value_ptr
/// \brief A smart pointer with copy semantics.
///
/// This class wraps a pointer of any class with a clone() method. It provides the following functionality: 
/// -# when the wrapper is copied the managed object is cloned.
/// -# when the wrapper is destroyed, the wrapped pointer is deleted.
///
/// Clones can be avoided by using move operations. Caution: For single objects only. Not suitable for arrays. Will leak memory This implementation is loosely based on the std::unique_ptr implementation found here: http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a01404.html.
///
/// This class was originally created to work around some memory leak issues, perceived or imaginary, with CERN ROOT serialization. What exactly those were, I can no longer remember. Likely it had to do with how ROOT takes ownership of Branch variables in a TTree, causing some incompatibility with std::unique_ptr.	
// TODO: there need to be some checks for nullptr before calling clone.
template<class T>
class value_ptr
{
public:
	
	/// No-arg constructor. Creates a null value_ptr.
	value_ptr()
		: ptr(nullptr) {;}
	
	/// Constructor. Takes ownership of pointer \p t. 
	explicit
	value_ptr(T* t)
		: ptr(t) {;}
	
	/// Copy constructor. Results in call to clone.
	value_ptr(const value_ptr& src)
		: ptr(src.ptr->clone()) {;}
	
	/// Move constructor. No call to clone.
	value_ptr(value_ptr&& src)
		: ptr(src.release()) {;}
			
	/// Destructor. Deletes managed pointer if any.
	~value_ptr() { reset(); }
	
	/// Assignment. Results in call to clone.
	value_ptr& operator=(value_ptr& other)
	{
		reset(other.ptr->clone());
		return *this;
	}
	
	/// Move assignment. No call to clone.
	value_ptr& operator=(value_ptr&& other)
	{
		reset(other.release());
		return *this;
	}
	
	/// Dereferences pointer to managed object.
	T& operator*() const
		{ return *get(); }
	
	/// Dereferences pointer to managed object.
	T* operator->() const
		{ return get();}
	
	/// Returns a raw pointer to the managed object.
	T* get() const
		{ return ptr; }
	
	/// Observer
	operator bool() const
		{ return get() == nullptr ? false : &value_ptr::ptr; }
	
	/// Take ownership of the pointer in the value_ptr. Returns the pointer and sets the value_ptr to nullptr.
	T* release()
	{
		T* rp = get();
		ptr = nullptr;
		return rp;
	}
	
	/// Deletes the owned pointer and takes ownership of the pointer \p p, whose default value is null. (Calling reset with no argument deletes the mananged memory)
	void reset(T* p = nullptr)
	{
		delete get();
		ptr = p;
	}
	
	/// Swap
	void swap(value_ptr& other)
		{ std::swap(ptr,other.ptr); }
	
	/// Swap using move
	void swap(value_ptr&& other)
		{ std::swap(ptr,other.ptr); }
	
private:
	T* ptr;
};

/// \related value_ptr
/// \brief Managed pointer equals.
template <class T, class U>
inline bool
operator==(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return x.get() == y.get(); }

/// \related value_ptr
/// \brief Managed pointer not equals.
template <class T, class U>
inline bool
operator!=(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return !(x.get() == y.get()); }

/// \related value_ptr
/// \brief Managed pointer less than.
template <class T, class U>
inline bool
operator<(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return x.get() < y.get(); }

/// \related value_ptr
/// \brief Managed pointer less than or equals.
template <class T, class U>
inline bool
operator<=(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return !(y.get() <= x.get()); }

/// \related value_ptr
/// \brief Managed pointer greater than.
template <class T, class U>
inline bool
operator>(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return y.get() < x.get(); }

/// \related value_ptr
/// \brief Managed pointer greater than or equals.
template <class T, class U>
inline bool
operator>=(const value_ptr<T>& x, const value_ptr<U>& y)
	{ return !(x.get() <= y.get()); }
	
} // namespace util 
} // namespace gex 



#endif
