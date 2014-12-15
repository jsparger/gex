//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef EJ299_DETECTOR_HH
#define EJ299_DETECTOR_HH

#include <gex/geom/Geometry.hh>

class EJ299Detector : public gex::geom::Geometry
{
public:
	virtual ~EJ299Detector() {;}
	virtual void construct(G4LogicalVolume* world) override;
	virtual void constructSDAndField(gex::sd::Sensitivizer*) override;
	
protected:
	G4LogicalVolume* ej299_logV;	
};

#endif