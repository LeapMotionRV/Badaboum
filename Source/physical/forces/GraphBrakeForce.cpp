#include "GraphBrakeForce.h"

namespace physical {

	GraphBrakeForce::GraphBrakeForce(float fV) 
	: m_fV(fV)
	, m_fDt(0.f)
	, m_pGraph(NULL)
	{

	}

	void GraphBrakeForce::apply(ParticleManager* pm) {
		if(m_fDt == 0.f || !m_pGraph)
			return;

		glm::vec3 brakeForce = glm::vec3(0.f);

		//Apply force on linked particles
		for(ParticleGraph::const_iterator itSpring=m_pGraph->begin(); itSpring!=m_pGraph->end(); ++itSpring) {
			unsigned int iP1 = itSpring->first;
			unsigned int iP2 = itSpring->second;

			brakeForce = m_fV/m_fDt * (pm->getVelocity(iP2) - pm->getVelocity(iP1));

			pm->addForce(iP1, brakeForce);
			pm->addForce(iP2, -brakeForce);
		}
	}
}