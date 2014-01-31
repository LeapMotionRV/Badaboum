#include <glm/gtc/random.hpp>
#include <string>

#include "Model.h"
#include "../util/LeapUtilGL.h"

namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		m_pLeapfrogSolver = new LeapfrogSolver();

		//data of the scene
		m_pParticleManager =  new ParticleManager();
		//m_pParticleManager->addRandomParticles(40);
		//m_pParticleManager->addParticle(glm::vec3(2.f, 2.f, 0.f),glm::vec3(0,0,0),1,glm::vec3(0,0,0),glm::vec3(0,0,1));
		
		m_pGround = new Ground(m_pLeapfrogSolver);

		m_pGround->addPolygonAndForce(
			glm::vec3(-25.f, -2.f, -25.f), glm::vec3(25.f, -2.f, -25.f), 
			glm::vec3(-25.f, -2.f, 25.f), glm::vec3(25.f, -2.f, 25.f), 
			glm::vec3(1.f, 1.f, 0.f), 2.f);


		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.05f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));

		m_pHookForce = new HookForce(0.01f, 0.01f);
		m_pBrakeForce = new BrakeForce(0.00001f, 0.001f);

		//m_pFacette = new Facette(glm::vec3(-3.f, 0.f, -3.f), glm::vec3(3.f, 0.f, -3.f), glm::vec3(3.f, -2.f, 3.f), glm::vec3(1.f, 0.f, 0.f));
		//m_pFacetteForce = new FacetteForce(m_pFacette, 1.f, m_pLeapfrogSolver);
		

	}

	Model::~Model(){
		delete m_pLeapfrogSolver;
		delete m_pParticleManager;
		for(unsigned int i = 0; i < m_pShapeArray.size(); ++i){
			delete m_pShapeArray[i];
		}
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
		delete m_pGround;
	}

	void Model::startSimulation(float dt) 
	{
		if(dt != 0) {
			m_pGravity->apply(m_pParticleManager);
			m_pGround->apply(m_pParticleManager, dt);

			//m_pFacetteForce->setDt(dt);
			//m_pFacetteForce->apply(m_pParticleManager);

			//m_pHookForce->apply(m_pParticleManager);
			//m_pBrakeForce->apply(m_pParticleManager);

			/*for(unsigned int i = 0; i < m_pGraphHookForceArray.size(); ++i){
				m_pGraphHookForceArray[i]->apply(m_pParticleManager);
			}
			for(unsigned int i = 0; i < m_pGraphBrakeForceArray.size(); ++i){
				m_pGraphBrakeForceArray[i]->setDt(dt);
				m_pGraphBrakeForceArray[i]->apply(m_pParticleManager);
			}*/

			for(unsigned int i = 0; i < m_pShapeArray.size(); ++i){
				m_pShapeArray[i]->applyInternalForces(m_pParticleManager, dt);
			}
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticle(){
		m_pParticleManager->addRandomParticles(1);
	}

	void Model::addRandomCube(){
		glm::vec3 center = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
		float size = glm::linearRand(0.5f,2.f);
		Cube* pCube = new Cube(m_pParticleManager, size, center);
		m_pShapeArray.push_back(pCube);
	}

	void Model::addRandomLine(){
		glm::vec3 startedPoint = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
		float size = 1.f;
		Line* pLine = new Line(m_pParticleManager, size, startedPoint);
		m_pShapeArray.push_back(pLine);
	}
}