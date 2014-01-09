#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


//c'est ParticleManager qui contient la structure ParticleState permettant d'accéder à l'état suivant de la particule
#include "ParticuleManager.h" 
#include "LeapfrogSolver.hpp"
#include "HookForce.hpp"


namespace physical {

	class Model {
	public:
		Model(unsigned int countParticules = 0){
			m_particuleManager =  physical::ParticuleManager();
			//m_particuleManager.addParticule(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 0.2f, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f));
			m_particuleManager.addRandomParticles(countParticules);
			m_leapfrogSolver = physical::LeapfrogSolver();
			m_hookForce = physical::HookForce(0.2f, 0.4f);
		}

		void startSimulation(float dt);

		ParticuleManager getParticuleManager(){return m_particuleManager;}
		LeapfrogSolver getLeapfrogSolver(){return m_leapfrogSolver;}
		HookForce getHookForce(){return m_hookForce;}
	private:
		ParticuleManager	m_particuleManager;
		LeapfrogSolver		m_leapfrogSolver;
		HookForce			m_hookForce;
	};

}

#endif