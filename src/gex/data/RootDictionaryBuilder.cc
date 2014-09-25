//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/data/RootDictionaryBuilder.hh"
#include "gex/data/IData.hh"
#include <sstream>

namespace gex {
namespace data {
	
std::unique_ptr<RootDictionaryBuilder> RootDictionaryBuilder::theInstance = nullptr;
std::mutex RootDictionaryBuilder::instanceMutex;
std::set<std::string> RootDictionaryBuilder::typeSet;
std::set<std::string> RootDictionaryBuilder::headerSet;
std::vector<std::string> RootDictionaryBuilder::typeVec;
std::vector<std::string> RootDictionaryBuilder::headerVec;
bool RootDictionaryBuilder::dictionaryBuilt = false;

RootDictionaryBuilder*
RootDictionaryBuilder::
GetRootDictionaryBuilder()
{
	std::lock_guard<std::mutex> lock(instanceMutex);
	
	if (nullptr == theInstance)
	{
		theInstance.reset(new RootDictionaryBuilder());
	}
	
	return theInstance.get();
}

void
RootDictionaryBuilder::
registerNewType(std::vector<std::string> types, std::vector<std::string> headers)
{
	std::lock_guard<std::mutex> lock(instanceMutex);
	addToDictionary(types, headers);
}

void
RootDictionaryBuilder::
registerData(IData* data)
{
	std::lock_guard<std::mutex> lock(instanceMutex);
	bool typeRegistered = (typeSet.count(data->getDataType()) != 0);
	if (false == typeRegistered)
	{
		std::vector<std::string> types = data->getDictionaryTypes();
		std::vector<std::string> headers = data->getDictionaryHeaders();
		addToDictionary(types, headers);
		typeSet.insert(data->getDataType());
	}
}

void 
RootDictionaryBuilder::
addToDictionary(std::vector<std::string> requestedTypes, std::vector<std::string> requestedHeaders)
{
	for (std::string& type : requestedTypes)
	{
		auto pair = typeSet.insert(type);
		bool isNewType = pair.second;
		if (isNewType)
		{
			typeVec.push_back(type);
		}
	}
	
	for (std::string& header : requestedHeaders)
	{
		auto pair = headerSet.insert(header);
		bool isNewHeader = pair.second;
		if (isNewHeader)
		{
			headerVec.push_back(header);
		}
	}
}

std::string
RootDictionaryBuilder::
concatenate(std::vector<std::string> itemVec)
{
	std::stringstream ss;
	for (auto it = itemVec.begin(); it != itemVec.end(); ++it)
	{
		ss << *it << ";";
	}
	
	return ss.str();
}

void 
RootDictionaryBuilder::
buildDictionary()
{
	std::lock_guard<std::mutex> lock(instanceMutex);
	if (false == dictionaryBuilt)
	{
		std::string types = concatenate(typeVec);
		std::string headers = concatenate(headerVec);
	
		std::lock_guard<std::mutex> lock(util::RootLock::MUTEX);
		std::cout << "types = " << types << "\n" << "headers = " << headers << "\n";
		std::cout << "INC_DIR = " << STRINGIFY(GEX_INCLUDE_DIR) << "\n";
		gInterpreter->AddIncludePath(STRINGIFY(GEX_INCLUDE_DIR));
	
		int returnVal = gInterpreter->GenerateDictionary(types.c_str(),headers.c_str());
		if (0 == returnVal)
		{
			dictionaryBuilt = true;
		}
		else
		{
			std::cerr << "RootDictionaryBuilder::registerNewType(): Error! Registration failed\n";
			std::exit(1);
			//TODO: throw real error
		}
	}
}

	
} // namespace data 
} // namespace gex 

