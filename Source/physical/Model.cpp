#include "Model.h"


namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		//data of the scene
		m_pParticleManager =  new ParticleManager();
		//m_particuleManager.addParticule(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 0.2f, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f));
		//m_particleManager.addRandomParticles(countParticles);

		m_pCube = new Cube(m_pParticleManager);
		m_pParticleManager->addParticle(glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.f, 0.f, 0.f), 0.2f, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
		m_pGround = new Polygon(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, -2.f, 0.f), 10.f, 20.f);
		
		//forces
		m_pLeapfrogSolver = new LeapfrogSolver();
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.01f, 0.f));
		m_pPolygonForce = new PolygonForce(m_pGround, 1.5f, m_pLeapfrogSolver);
		//m_pHookForce = new HookForce(0.01f, 0.01f);

		m_pGraphHookForce = new GraphHookForce(0.01f, 0.01f);
		//m_pGraphBrakeForce = new GraphBrakeForce(0.1f);

		m_pGraphHookForce->setGraph(m_pCube->getCubeGraph());
		//m_pGraphBrakeForce->setGraph(m_pCube->getCubeGraph());
	}

	void Model::startSimulation(float dt) 
	{
		if(dt !=0) {
		//	m_pGravity->apply(m_pParticleManager);
			//m_pHookForce->apply(m_pParticleManager);

			m_pGraphHookForce->apply(m_pParticleManager);
			//m_pGraphBrakeForce->setDt(dt);
			//m_pGraphBrakeForce->apply(m_pParticleManager);

			m_pPolygonForce->setDt(dt);
			m_pPolygonForce->apply(m_pParticleManager);
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}
}