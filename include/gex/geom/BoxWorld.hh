//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_GEOM_BOX_WORLD_HH
#define GEX_GEOM_BOX_WORLD_HH

class G4VPhysicalVolume;
class G4Material;

namespace gex {
namespace geom {

/// \class BoxWorld
/// \brief A class that creates a simple rectangular prism world volume filled with Air.  
///
///
class BoxWorld
{
public:
	/// Constructor. Give the half height, half width, and half depth of the world volume.
	BoxWorld(double hx, double hy, double hz);
	virtual ~BoxWorld() {;}
	
	/// Construct the world volume and return it.
	G4VPhysicalVolume* construct();
	
protected:
	double hx, hy, hz;
	G4Material* material;
};
	
} // namespace geom 
} // namespace gex 

#endif
