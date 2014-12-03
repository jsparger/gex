//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#include "gex/pga/SphericalTarget.hh"
#include "gex/pga/EnergyDistribution.hh"
#include "gex/pga/AngularDistribution.hh"
#include "gex/pga/SpatialDistribution.hh"
#include "gex/pga/ParticleDistribution.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
#include <cmath>
#include "G4Event.hh"
#include "G4Threading.hh"
#include <iomanip>
#include "G4ThreeVector.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "gex/data/UserInfoAccess.hh"
#include "gex/util/Access.hh"
#include "gex/util/make_unique.hh"
#include "gex/data/PrimaryVertexData.hh"


namespace gex {
namespace pga {
	
SphericalTarget::
SphericalTarget(G4ThreeVector tPos, double tRad,
					EnergyDistribution* eDist, SpatialDistribution* pDist, 
					ParticleDistribution* parDist, double recDist)
	: GenericSource(eDist,0,pDist,parDist), targetPos(tPos), up(0,0,1), 
					targetRadius(tRad), recomputeDistance(recDist), acceptanceProb(0), firstTime(true) 
					
{
	random.SetSeed(time(nullptr));
}

// void
// SphericalTarget::
// GeneratePrimaries(G4Event* theEvent)
// {
// 	// generate positions and calculate resulting acceptance probability
// 	// assuming an isotropic source. If we generate a random number that
// 	// falls within acceptance prob, continue.
// 	bool recomputeRotation = false;
// 	G4ThreeVector toCenter;
// 	double phi = 0;
// 	double r = 0;
// 	thread_local static int nSamples = 0;
// 	do
// 	{
// 		pos = spatialDist->getPosition();
// 		bool recomputeSolidAngle = (recomputeDistance < (lastRecomputePos-pos).mag() || firstTime);
// 		r = G4UniformRand();
// 		++nSamples;
// 		if (recomputeSolidAngle)
// 		{
// 			recomputeRotation = true;
// 			lastRecomputePos = pos;
// 			firstTime = false;			
// 			toCenter = targetPos - pos;
// 			G4ThreeVector toBound = toCenter.orthogonal().unit()*targetRadius + toCenter;
// 			phi = toCenter.angle(toBound);
// 			acceptanceProb = (1-std::cos(phi))/2;
// 			// std::cout << "pos = " << pos/m << " r = " << r << "acceptanceProb = " << acceptanceProb << "\n"; 
// 		}
// 		
// 	} while(r > acceptanceProb);
// 		
// 	// generate vector within the cone with aperture size 2*phi directed at target.
// 	// G4RandFlat flat(G4Random::getTheEngine());
// 	double rTheta = G4UniformRand()*2*pi;//flat.fire(0, 2*pi);
// 	double rZ = G4UniformRand()*(1-std::cos(phi)) + std::cos(phi);//flat.fire(std::cos(phi), 1);
// 	double c = std::sqrt(1-rZ*rZ);
// 	double rX = c*std::cos(rTheta);
// 	double rY = c*std::sin(rTheta);
// 	G4ThreeVector v = G4ThreeVector(rX,rY,rZ).unit();
// 	
// 	// rotate v to point at target.
// 	//std::cout << "recomputeRotation =" << recomputeRotation << "\n";
// 	thread_local static int nEvents = 0;
// 	if (recomputeRotation)
// 	{
// 		std::cout << "threadID = " << G4Threading::G4GetThreadId() << " nEvents = " << nEvents << " nSamples = " << nSamples << " pos = " << pos/m << " toCenter = " << toCenter/m << " rotAxis = " << rotAxis << "\n";
// 		rotAxis = up.cross(toCenter.unit());
// 	}
// 	double rotAngle = up.angle(toCenter);
// 	G4ThreeVector momentumDirection = v.rotate(rotAxis,rotAngle);
// 	
// 	//set the properties of the primary
// 	gun->SetParticleDefinition(particleDist->getParticleType());
// 	gun->SetParticleEnergy(energyDist->getEnergy());
// 	gun->SetParticleMomentumDirection(momentumDirection);
// 	gun->SetParticlePosition(pos);
// 	
// 	// generate the primary
// 	gun->GeneratePrimaryVertex(theEvent); 
// 	++nEvents;
// 	nSamples = 0;
// 	
// }

void
SphericalTarget::
GeneratePrimaries(G4Event* theEvent)
{		
	if (firstTime)
	{
		// this throws away one decay...
		pos = spatialDist->getPosition(1,theEvent);
	}
	
	// attach a NamedData to the event
	data::UserInfoAccess<G4Event> infoAccess;
	infoAccess.set(theEvent,std::make_unique<data::NamedData>());
	
	// calculate fractional solid angle of target at current location.
	bool recompute = (recomputeDistance < (lastRecomputePos-pos).mag() || firstTime);
	
	if (recompute)
	{
		lastRecomputePos = pos;
		firstTime = false;			
		toCenter = targetPos - pos;
		G4ThreeVector toBound = toCenter.orthogonal().unit()*targetRadius + toCenter;
		phi = toCenter.angle(toBound); 
		//phi = 0.0678954792*rad; // THIS WAS A TEST TO FIND A BUG IN THE OLD CODE! THIS LINE IS INCORRECT!
		acceptanceProb = (1-std::cos(phi))/2;
	}
	
	// sample from inverse binomial distribution to see how many decays before
	// we shoot a particle in the target cone.
	unsigned int numDecays = random.NegativeBinomial(1,acceptanceProb);
	
	// request the position after the sampled number of decays.
	// pos = spatialDistribution->getPosition(numDecays);
	pos = spatialDist->getPosition(numDecays,theEvent);
	// if (recompute)
	// {
	// 	std::cout << "pos = " << pos/m << " EventID = " << theEvent->GetEventID() << " numDecays = " << numDecays << "\n";
	// }
	// TODO: check to make sure we have not travelled so far that we will not hit the target.
	// recalculate target direction so we are actually shooting at the target even if 
	// the solid angle is the wrong size.
	toCenter = targetPos - pos; // TODO: why is this calculated again?
	G4ThreeVector toCenterDir = toCenter.unit();
	
	// generate vector within the cone with aperture size 2*phi directed at target.
	double rTheta = G4UniformRand()*2*pi;//flat.fire(0, 2*pi);
	double rZ = G4UniformRand()*(1-std::cos(phi)) + std::cos(phi);//flat.fire(std::cos(phi), 1);
	double c = std::sqrt(1-rZ*rZ);
	double rX = c*std::cos(rTheta);
	double rY = c*std::sin(rTheta);
	G4ThreeVector v = G4ThreeVector(rX,rY,rZ).unit();
	
	// Check to see if toCenter is parallel to up (the z-axis) to within some tolerance.
	if (1 - std::abs(up.dot(toCenterDir)) > 1e-9)
	{
		// if not parallel, rotate v to point at target.
		// (this will fail if up is parallel to toCenterDir)
		if (recompute)
		{
			rotAxis = up.cross(toCenterDir);
		}
		double rotAngle = up.angle(toCenter);
		v = v.rotate(rotAxis,rotAngle);
	}
	else
	{
		// if it is parallel, check to see whether it is facing in + or - z direction.
		// if negative, flip z of vector.
		double cz = toCenterDir.z();
		double sign = (0 < cz) - (cz < 0);
		v.setZ(v.z()*sign);
	}
	
	//set the properties of the primary
	gun->SetParticleDefinition(particleDist->getParticleType(theEvent));
	gun->SetParticleEnergy(energyDist->getEnergy(theEvent));
	gun->SetParticleMomentumDirection(v);
	gun->SetParticlePosition(pos);
	
	// fill in source data for event
	fillPrimaryVertexData(theEvent);
	
	// generate the primary
	gun->GeneratePrimaryVertex(theEvent);
}

void
SphericalTarget::
fillPrimaryVertexData(G4Event* theEvent)
{
	data::UserInfoAccess<G4Event> infoAccess;
	data::NamedData* nd = infoAccess.get(theEvent);
		
	auto* pvData = new data::PrimaryVertexData();
		
	pvData->energy = gun->GetParticleEnergy();
	pvData->momentum = gun->GetParticleMomentum();
	pvData->globalTime = gun->GetParticleTime();
	pvData->numParticles = gun->GetNumberOfParticles();
	
	G4ThreeVector md = gun->GetParticleMomentumDirection();
	pvData->setMomentumDirection(md.x(), md.y(), md.z());
	
	G4ThreeVector p = gun->GetParticlePosition();
	pvData->setPosition(p.x(), p.y(), p.z());
	
	if (G4Gamma::Definition() == gun->GetParticleDefinition())
	{
		pvData->particleType = 1;
	}
	else if (G4Neutron::Definition() == gun->GetParticleDefinition())
	{
		pvData->particleType = 2;
	}
	else
	{
		pvData->particleType = 3;
	}
	
	util::get_access(*nd).insert("primaryVertex", pvData);
}
	
} // namespace pga 	
} // namespace gex 











