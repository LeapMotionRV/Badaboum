#include "ConstantForce.h"

namespace physical 
{
	void ConstantForce::apply(ParticleManager* pm){
		std::vector<glm::vec3> forceArray = pm->getForceArray();
		for(size_t i = 0; i < forceArray.size(); i++){
			pm->addForceToParticle(m_force, i);
		}
	}

	ConstantForce::~ConstantForce(){}
}
