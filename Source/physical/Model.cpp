#include "Model.h"


namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		m_pLeapfrogSolver = new LeapfrogSolver();

		//data of the scene
		m_pParticleManager =  new ParticleManager();
		m_pParticleManager->addRandomParticles(countParticles);
		
		m_pGround = new Ground(m_pLeapfrogSolver);
		m_pGround->addPolygonAndForce(glm::vec3(-25.f, -2.f, -25.f), glm::vec3(25.f, -2.f, -25.f), glm::vec3(-25.f, -2.f, 25.f), glm::vec3(25.f, -2.f, 25.f), glm::vec3(1.f, 1.f, 0.f), 2.f);

		//Cube* pCube1 = new Cube(m_pParticleManager, 2.f, glm::vec3(0.f, 4.f, 0.f));
		//Cube* pCube2 = new Cube(m_pParticleManager, 2.f, glm::vec3(0.4f, 10.f, 0.f));
		//m_pShapeArray.push_back(pCube1);
		//m_pShapeArray.push_back(pCube2);
		
		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.01f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));

		m_pHookForce = new HookForce(0.01f, 0.01f);
		m_pBrakeForce = new BrakeForce(0.00001f, 0.001f);

		//this->addHookAndBrakeForceToShape(pCube1, 0.02f, 2.f, 0.01f);
		//this->addHookAndBrakeForceToShape(pCube2, 0.02f, 2.f, 0.01f);

		Flag* pFlag = new Flag(0.4f, 3.f, 3.f, 3.f, 3, 3, 3);
		m_pShapeArray.push_back(pFlag);
	}

	Model::~Model(){
		delete m_pLeapfrogSolver;
		//physical objects
		delete m_pParticleManager;
		for(unsigned int i = 0; i < m_pShapeArray.size(); ++i){
			delete m_pShapeArray[i];
		}
		//forces
		delete m_pGravity;
		delete m_pWind;
		delete m_pHookForce;
		delete m_pBrakeForce;
		for(unsigned int i = 0; i < m_pGraphHookForceArray.size(); ++i){
			delete m_pGraphHookForceArray[i];
		}
		for(unsigned int i = 0; i < m_pGraphBrakeForceArray.size(); ++i){
			delete m_pGraphBrakeForceArray[i];
		}
		//getters - physical object + forces
		delete m_pGround;
	}

	void Model::startSimulation(float dt) 
	{
		if(dt != 0) {
			//m_pGravity->apply(m_pParticleManager);
			//m_pWind->apply(m_pParticleManager);

			//m_pHookForce->apply(m_pParticleManager);
			//m_pBrakeForce->apply(m_pParticleManager);

			/*for(unsigned int i = 0; i < m_pGraphHookForceArray.size(); ++i){
				m_pGraphHookForceArray[i]->apply(m_pParticleManager);
			}
			for(unsigned int i = 0; i < m_pGraphBrakeForceArray.size(); ++i){
				m_pGraphBrakeForceArray[i]->setDt(dt);
				m_pGraphBrakeForceArray[i]->apply(m_pParticleManager);
			}
			*/
			//m_pGround->apply(this->getFlag()->getParticleManager(), dt);

			//flag
			this->getFlag()->applyInternalForces(dt);
			this->getFlag()->update(dt);
		}
		//m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addHookAndBrakeForceToShape(Shape* pShape, float raideur, float longueur, float fV){
		GraphHookForce* pGraphHookForce = new GraphHookForce(raideur, longueur); //0.01f 1.f // for the line : 0.1f, 2.f //0.1 0.1
		pGraphHookForce->setGraph(pShape->getGraph());
		GraphBrakeForce* pGraphBrakeForce = new GraphBrakeForce(fV); //0.001f // for the line : 0.01f
		pGraphBrakeForce->setGraph(pShape->getGraph());
		
		m_pGraphHookForceArray.push_back(pGraphHookForce);
		m_pGraphBrakeForceArray.push_back(pGraphBrakeForce);
	}
}