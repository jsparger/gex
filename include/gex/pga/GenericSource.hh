//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef GEX_PGA_GENERIC_SOURCE_HH
#define GEX_PGA_GENERIC_SOURCE_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <memory>

namespace gex {
namespace pga {

	class EnergyDistribution;
	class AngularDistribution;
	class SpatialDistribution;
	class ParticleDistribution;

	/// \class GenericSource
	/// \brief A composite class for modeling sources.
	///
	/// GenericSource is a primary generator action based on the idea that the energy distribution, angular distribution, spatial distribution, and particle type of sources are often independent of one another. The user needs to supply an EnergyDistribution, AngularDistribution, SpatialDistribution, and ParticleDistribution to create a source using this class. GenericSource will query these classes to generate primaries. Multiple inheritance may be used when there are dependencies between the distributions.
	class GenericSource : public G4VUserPrimaryGeneratorAction
	{
	public:
		/// Constructor. Takes a raw pointer to each distribution.
		GenericSource(EnergyDistribution* eDist, AngularDistribution* aDist, 
						SpatialDistribution* pDist, ParticleDistribution* parDist);
						
		/// Destructor (does nothing)
		virtual ~GenericSource() {;}
	
		// From G4VUserPrimaryGeneratorAction
		virtual void GeneratePrimaries(G4Event* e) override;

	protected:		
		EnergyDistribution* energyDist;
		AngularDistribution* angularDist;
		SpatialDistribution* spatialDist;
		ParticleDistribution* particleDist;
		std::unique_ptr<G4ParticleGun> gun;
	};
	
} // namespace pga 
} // namespace gex 

#endif
