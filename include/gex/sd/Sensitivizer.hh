//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_SD_SENSITIVIZER_HH
#define GEX_SD_SENSITIVIZER_HH

#include "G4LogicalVolume.hh"

namespace gex {
namespace sd {

/// \class Sensitivizer
/// \brief Abstract base class for Sensitivizers used with GeometryManager
///
/// This class is used to make a volume into a sensitive detector.
class Sensitivizer
{
public:
	virtual ~Sensitivizer(){;}
	
	/// This method should contain the code to turn the volume into a sensitive detector.
	virtual void makeSensitive(G4LogicalVolume* volume) = 0;
};

} // namespace geom
} // namespace gex

#endif
