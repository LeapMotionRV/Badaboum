#include <math.h>
#include <glm/glm.hpp>
#include <iostream>

#include "FacetteForce.h"
#include "../maths.h"


namespace physical 
{
	void FacetteForce::setDt(float dt) {
		m_fDt = dt;
	}

	bool FacetteForce::isParticleInFacet(ParticleManager* pm, int particleIndex){
		for(unsigned int i = 0; i < m_pFacette->getPointArray().size(); ++i){
			if(*m_pFacette->getPointArray()[i] == pm->getPositionArray()[particleIndex])
				return true;
		}
		return false;
	}

	void FacetteForce::apply(ParticleManager* pm){
		glm::vec3 intersection;
		glm::vec3 normal;
		
		//boucle sur toutes les particules
		for (unsigned int particleIndex = 0; particleIndex < pm->getPositionArray().size(); ++particleIndex) 
		{
			//particle is part of the facet
			if(isParticleInFacet(pm, particleIndex))
				continue;

			ParticleState nextParticleState = m_Solver->getNextState(particleIndex, pm, m_fDt);
			
			/*INTERSECTION BETWEEN VECTOR AND PLANE*/
			if(intersectFacette(m_pFacette, pm->getPositionArray()[particleIndex], nextParticleState.m_position, &intersection, &normal ))
 			{
				//il y a intersection alors on applique une force pour repousser la particule
				glm::vec3 forceRepulse;
				//formule fournie dans l'énoncé
				forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm->getMassArray()[particleIndex]/m_fDt) * normal;
				//pm.resetForceOfParticle(particleIndex);
				pm->setForceOfParticle(forceRepulse, particleIndex);
			}
		}
	}
}
