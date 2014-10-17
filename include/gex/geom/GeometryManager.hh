//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_GEOM_GEOMETRY_MANAGER_HH
#define GEX_GEOM_GEOMETRY_MANAGER_HH

#include "G4VUserDetectorConstruction.hh"
#include <memory>
#include "gex/geom/Geometry.hh"

namespace gex {
namespace geom {

/// \class GeometryManager
/// \brief Handles the construction of Geometry elements in the world volume.
///
/// GeometryManager lets you combine several independent Geometry elements into a single geometry. It also handles the creation of sensitive detectors using a user provided Sensitivizer.
class GeometryManager : public G4VUserDetectorConstruction
{
public:
	/// Constructor. Provide the GeometryManager with the world volume and a sensitivizer.
	GeometryManager(G4VPhysicalVolume* worldPhys, sd::Sensitivizer* sens);
	virtual ~GeometryManager(){;}
	
	/// Add a Geometry. The GeometryManager will make sure all registered Geometries are constructed within the world volume.
	virtual void addGeometry(std::unique_ptr<Geometry> geom);
	
	/// Called by Geant4
	virtual G4VPhysicalVolume* Construct() override;
	/// Called by Geant4
	virtual void ConstructSDandField() override;
protected:
	G4VPhysicalVolume* worldPhys;
	sd::Sensitivizer* sensitivizer;
	std::vector<std::unique_ptr<Geometry>> geometryVec;
};
	
} // namespace geom
} // namespace gex

#endif
