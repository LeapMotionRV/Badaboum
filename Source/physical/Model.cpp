#include <glm/gtc/random.hpp>

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

		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.01f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));

		m_pHookForce = new HookForce(0.01f, 0.01f);
		m_pBrakeForce = new BrakeForce(0.00001f, 0.001f);

		//flag
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
			m_pGravity->apply(m_pParticleManager);
			//m_pWind->apply(m_pParticleManager);
			m_pGround->apply(m_pParticleManager, dt);

			//m_pHookForce->apply(m_pParticleManager);
			//m_pBrakeForce->apply(m_pParticleManager);

			for(unsigned int i = 0; i < m_pGraphHookForceArray.size(); ++i){
				m_pGraphHookForceArray[i]->apply(m_pParticleManager);
			}
			for(unsigned int i = 0; i < m_pGraphBrakeForceArray.size(); ++i){
				m_pGraphBrakeForceArray[i]->setDt(dt);
				m_pGraphBrakeForceArray[i]->apply(m_pParticleManager);
			}
			
			//flag
			this->getFlag()->applyInternalForces(dt);
			this->getFlag()->update(dt);
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticle(){
		m_pParticleManager->addRandomParticles(1);
	}

	void Model::addRandomCube(){
		glm::vec3 center = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(-5.f,5.f), glm::linearRand(-5.f,5.f));
		Cube* pCube = new Cube(m_pParticleManager, glm::linearRand(0.5f,5.f), center);
		m_pShapeArray.push_back(pCube);

		this->addHookAndBrakeForceToShape(pCube, 0.02f, 2.f, 0.01f);
	}

	void Model::addRandomLine(){
		glm::vec3 startedPoint = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(-5.f,5.f), glm::linearRand(-5.f,5.f));
		Line* pLine = new Line(m_pParticleManager, 1.f, startedPoint);
		m_pShapeArray.push_back(pLine);
		
		this->addHookAndBrakeForceToShape(pLine, 0.5f, 1.f, 0.05f);
	}

	void Model::addHookAndBrakeForceToShape(Shape* pShape, float raideur, float longueur, float fV){
		GraphHookForce* pGraphHookForce = new GraphHookForce(raideur, longueur);
		pGraphHookForce->setGraph(pShape->getGraph());
		GraphBrakeForce* pGraphBrakeForce = new GraphBrakeForce(fV);
		pGraphBrakeForce->setGraph(pShape->getGraph());
		
		m_pGraphHookForceArray.push_back(pGraphHookForce);
		m_pGraphBrakeForceArray.push_back(pGraphBrakeForce);
	}
}