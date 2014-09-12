//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_DATA_DATAMODULE
#define GEX_DATA_DATAMODULE

#include "gex/data/IData.hh"
#include <memory>
#include <string>

namespace gex {
namespace data {

/// \class DataModule
/// \brief An abstract base class for modules which produce data.
///
/// DataModule is an abstract base class for modules which produce data. One such use case would be a sensitive detector. It provides an interface for creating and providing the module with data of a specific type. This allows for a DataModule to operate on data without managing its lifetime, storage, etc.
struct DataModule
{
	/// Constructor. Requires a name for the module.
	DataModule(const std::string& n)
		: moduleName(n) {;}
	virtual ~DataModule() {;}
	/// Asks the module to create an object of the type of data it operates on.
	virtual std::unique_ptr<IData> createData() = 0;
	/// Sets the data object for the module to use.
	virtual void setData(IData* data) = 0;
	/// Get the module's name.
	virtual std::string getModuleName() { return moduleName; }
protected:
	const std::string moduleName;
	
};
	
} // namespace data 
} // namespace gex 

#endif
