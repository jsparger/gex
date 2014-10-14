#ifndef MY_DETECTOR_HH
#define MY_DETECTOR_HH

#include <gex/geom/Geometry.hh>

class MyDetector : public gex::geom::Geometry
{
public:
	virtual ~MyDetector() {;}
	virtual void construct(G4LogicalVolume* world) override;
	virtual void constructSDAndField(sd::Sensitivizer*) override;
	
protected:
	G4LogicalVolume* naiLog;
};

#endif