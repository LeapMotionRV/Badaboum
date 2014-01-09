#include "Model.h"


namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		//data of the scene
		m_particleManager =  ParticleManager();
		//m_particuleManager.addParticule(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 0.2f, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f));
		m_particleManager.addRandomParticles(countParticles);
		m_ground = Polygon(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, -5.f, 0.f), 10.f, 20.f);
		
		//forces
		m_leapfrogSolver = LeapfrogSolver();
		m_gravity = ConstantForce(glm::vec3(0.f, -0.01f, 0.f));
		m_polygonForce = PolygonForce(&m_ground, 1.f, &m_leapfrogSolver);
		m_hookForce = HookForce(0.2f, 0.4f);
	}

	void Model::startSimulation(float dt) 
	{
		if(dt !=0) {
			m_gravity.apply(m_particleManager);
			//m_hookForce.apply(m_particleManager);
			//m_polygonForce.setDt(dt);
			//m_polygonForce.apply(m_particleManager);
		}
		m_leapfrogSolver.solve(m_particleManager, dt);
	}
}