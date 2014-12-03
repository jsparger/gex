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