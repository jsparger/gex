#include "MySensitivizer.hh"

MySensitivizer::
MySensitivizer(const std::string fileName, const std::string treeName)
{
	// TODO: implement
}

void 
MySensitivizer::
makeSensitive(G4LogicalVolume* vol)
{
	if (false == G4Threading::IsWorkerThread()) { return; }
	
	auto* energy = ua::create<sd::EnergyDepSD>("energy");
	auto* time = ua::create<sd::TimeOfHitSD>("time");
	auto* distance = ua::create<sd::PrimaryVertexSD>("primaryVertex");
	
	
}