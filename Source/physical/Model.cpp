#include "Model.h"


namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		//data of the scene
		m_pParticleManager =  new ParticleManager();
		m_pParticleManager->addRandomParticles(countParticles);
		
		m_pGround = new Polygon(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, -2.f, 0.f), 100.f, 100.f);
		//m_pCube = new Cube(m_pParticleManager);
		//m_pLine = new Line(m_pParticleManager);
		
		//forces
		m_pLeapfrogSolver = new LeapfrogSolver();

		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.01f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));

		m_pPolygonForce = new PolygonForce(m_pGround, 2.f, m_pLeapfrogSolver);
		
		//m_pHookForce = new HookForce(0.01f, 0.01f);
		//m_pBrakeForce = new BrakeForce(0.00001f, 0.001f);
		
		m_pGraphHookForce = new GraphHookForce(0.01f, 1.f); //0.01f 1.f // for the line : 0.1f, 2.f
		m_pGraphHookForce->setGraph(m_pCube->getGraph());
		m_pGraphBrakeForce = new GraphBrakeForce(0.001f); //0.001f      // for the line : 0.01f
		m_pGraphBrakeForce->setGraph(m_pCube->getGraph());
	}

	void Model::startSimulation(float dt) 
	{
		if(dt != 0) {
			m_pGravity->apply(m_pParticleManager);
			//m_pWind->apply(m_pParticleManager);

			//m_pHookForce->apply(m_pParticleManager);
			//m_pBrakeForce->apply(m_pParticleManager);

			m_pGraphHookForce->apply(m_pParticleManager);
			m_pGraphBrakeForce->setDt(dt);
			m_pGraphBrakeForce->apply(m_pParticleManager);

			m_pPolygonForce->setDt(dt);
			m_pPolygonForce->apply(m_pParticleManager);
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}
}