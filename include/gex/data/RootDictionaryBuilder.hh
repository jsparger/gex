//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_ROOTDICTIONARYBUILDER_HH
#define GEX_DATA_ROOTDICTIONARYBUILDER_HH

#include "TCint.h"
#include <memory>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <set>
#include <vector>
#include "gex/data/IData.hh"
#include "gex/util/RootLock.hh"
#include "gex/util/STRINGIFY.hh"

namespace gex {
namespace data {
	
class IData;

/// \class RootDictionaryBuilder
/// \brief Uses ROOT to automatically build and link ROOT dictionaries for registered types at runtime.
///
/// RootDictionaryBuilder will automatically build and link ROOT dictionaries for registered types at runtime. This allows the type of data to be stored using ROOT to be decided at runtime. This is important because it allows data to be output as a collection of different types of data instead of tying the framework to a single predefined data class which cannot be sufficient for all applications.
///
/// RootDictionaryBuilder is threadsafe.
class RootDictionaryBuilder
{
public:
	/// Get the global RootDictionaryBuilder instance.
	static RootDictionaryBuilder* GetRootDictionaryBuilder();
	
	/// Register a new type. This method of registration relies on the existence of static methods GetDictionaryTypes() and GetDictionaryHeaders(). Examples of these methods can be seen in IData implementations like data::EnergyData present in this library.
	template <typename T>
	void registerNewType()
	{
		// build dictionary only once per type.
		static bool typeRegistered = false;
		
		std::lock_guard<std::mutex> lock(instanceMutex);
		if (false == typeRegistered)
		{
			std::vector<std::string> types = T::GetDictionaryTypes();
			std::vector<std::string> headers = T::GetDictionaryHeaders();
			addToDictionary(types, headers);
			typeRegistered = true;
			
		}
	}
	
	/// Register a new type with type inference. See the no-arg registerNewType<T>() for a detailed description.
	template <typename T>
	void registerNewType(T*)
	{
		registerNewType<T>();
	}
	
	/// Registers a new type given the dependent types and headers.
	void registerNewType(std::vector<std::string> types, std::vector<std::string> headers);
	
	/// Registers an IData type.
	void registerData(IData* data);
	
	/// Builds the ROOT dictionary for all the types that have been registered. This method is safe to call multiple times from multiple threads after all the necessary types have been registered. Only the first call will cause the dictionary to be generated. It will not be rebuilt with subsequent calls.
	void buildDictionary();
	
protected:
	RootDictionaryBuilder();
	virtual ~RootDictionaryBuilder() {;}
	
	void addToDictionary(std::vector<std::string> typeVec, std::vector<std::string> headerVec);
	std::string concatenate(std::vector<std::string> itemVec);

protected:
	static std::mutex instanceMutex;
	static std::unique_ptr<RootDictionaryBuilder> theInstance;
	friend std::unique_ptr<RootDictionaryBuilder>::deleter_type;
	
	static std::set<std::string> typeSet;
	static std::set<std::string> headerSet;
	static std::vector<std::string> typeVec;
	static std::vector<std::string> headerVec;
	static std::string gex_include_dir;
	static bool dictionaryBuilt;
	
};
	
} // namespace data 
} // namespace gex 


//#endif
#endif
