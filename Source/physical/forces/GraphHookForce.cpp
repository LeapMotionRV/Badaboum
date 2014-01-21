#include "GraphHookForce.h"
#include <algorithm> 
#include <glm/glm.hpp>

namespace physical {
	GraphHookForce::GraphHookForce(float raideur, float longueur){
		m_fK = raideur;
		m_fL = longueur;
		m_pGraph = NULL;
	}

	void GraphHookForce::apply(ParticleManager* pm){
		if(!m_pGraph)
			return;

		float epsilon = 0.001;
		float d = 0.f;
		glm::vec3 p1p2 = glm::vec3(0.f);
		glm::vec3 forceHook = glm::vec3(0.f);

		//Apply force on linked particles
		for(ParticleGraph::const_iterator itSpring=m_pGraph->begin(); itSpring!=m_pGraph->end(); ++itSpring) {
			unsigned int iP1 = itSpring->first;
			unsigned int iP2 = itSpring->second;

			p1p2 = pm->getPosition(iP2)-pm->getPosition(iP1);
			d = sqrt(glm::dot(p1p2, p1p2));
			forceHook = (m_fK * (1-(m_fL/std::max(d, epsilon)))) * p1p2;

			pm->addForceToParticle(forceHook, iP1);
			pm->addForceToParticle(-forceHook, iP2);	
		}
	}
}