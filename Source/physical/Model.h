#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


//c'est ParticleManager qui contient la structure ParticleState permettant d'acc�der � l'�tat suivant de la particule
#include "ParticleManager.h" 
#include "LeapfrogSolver.h"
#include "HookForce.h"


namespace physical {

	class Model {
	public:
		Model(unsigned int countParticules = 0){
			m_particleManager =  physical::ParticleManager();
			//m_particuleManager.addParticule(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 0.2f, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f));
			m_particleManager.addRandomParticles(countParticules);
			m_leapfrogSolver = physical::LeapfrogSolver();
			m_hookForce = physical::HookForce(0.2f, 0.4f);
		}

		void startSimulation(float dt);

		ParticleManager getParticuleManager(){return m_particleManager;}
		LeapfrogSolver getLeapfrogSolver(){return m_leapfrogSolver;}
		HookForce getHookForce(){return m_hookForce;}
	private:
		ParticleManager		m_particleManager;
		LeapfrogSolver		m_leapfrogSolver;
		HookForce			m_hookForce;
	};

}

#endif