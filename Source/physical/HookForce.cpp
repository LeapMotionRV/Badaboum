#include <algorithm>

#include "HookForce.hpp"
#include "ParticuleManager.h"


namespace physical 
{

	void HookForce::apply(ParticuleManager& pm)
	{
		const float epsilon = 0.001f;
		std::vector<glm::vec3> positionArray = pm.getPositionArray();

		//pour chaque particule on regarde toutes les autres et on calcule la force qu'elles exercent dessus
		for(size_t particleIdx = 0; particleIdx < pm.getForceArray().size(); particleIdx++)
		{
			for(size_t otherParticleIdx = 0; otherParticleIdx < pm.getForceArray().size(); otherParticleIdx++)
			{
				if(otherParticleIdx != particleIdx )
				{
					glm::vec3 P1P2 = positionArray[otherParticleIdx] - positionArray[particleIdx];
					float dP1P2 = glm::length(positionArray[otherParticleIdx] - positionArray[particleIdx]);
					glm::vec3 newForce = m_fK * (1-(m_fL / std::max (dP1P2, epsilon))) * (P1P2);
					//est-ce qu'il faut vraiment adder ou plutôt setter ?
					pm.addForceToParticule(newForce, particleIdx);
				}
			}
		}
	}

	HookForce::~HookForce(){}
}
