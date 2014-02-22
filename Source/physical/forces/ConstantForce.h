#ifndef _IMAC3_CONSTANTFORCE_HPP
#define _IMAC3_CONSTANTFORCE_HPP

#include <glm/glm.hpp>

#include "Force.h"
#include "../ParticleManager.h"

namespace physical 
{
	class ConstantForce : public Force
	{
	public:
		ConstantForce(){m_force = glm::vec3(0.f, 0.9f, 0.f);};
		ConstantForce(glm::vec3 force):m_force(force){};
		~ConstantForce();

		void apply(ParticleManager* pm);

		//getter
		float getForce(){return m_force.y;}

		//setter
		void setForce(glm::vec3 force){m_force=force;}
		
	private:
		glm::vec3 m_force;
	};
}

#endif // IMAC3_CONSTANTFORCE_HPP
