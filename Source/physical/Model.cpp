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
		m_pGround = new Ground(m_pLeapfrogSolver);
		m_pGround->addPolygonAndForce(
			glm::vec3(-25.f, -2.f, -25.f), glm::vec3(25.f, -2.f, -25.f), 
			glm::vec3(-25.f, -2.f, 25.f), glm::vec3(25.f, -2.f, 25.f), 
			glm::vec3(1.f, 1.f, 0.f), 2.0f);

		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.05f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));
	}

	Model::~Model(){
		delete m_pLeapfrogSolver;
		delete m_pParticleManager;
		for(unsigned int i = 0; i < m_pShapeArray.size(); ++i){
			delete m_pShapeArray[i];
		}
		delete m_pGravity;
		delete m_pWind;
		//delete m_pHookForce;
		//delete m_pBrakeForce;
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

			for(unsigned int i = 0; i < m_pShapeArray.size(); ++i){
				m_pShapeArray[i]->applyInternalForces(m_pParticleManager, dt);
				m_pShapeArray[i]->applyExternalForces(m_pParticleManager, dt);
			}
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticle(){
		m_pParticleManager->addRandomParticles(1);
	}

	void Model::addRandomCube(){
		//glm::vec3 randomCenter = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
		//float randomSize = glm::linearRand(0.5f,2.f);
		//Cube* pCube = new Cube(m_pParticleManager, size, center);
		Cube* pCube = new Cube(m_pLeapfrogSolver, m_pParticleManager, 1.f, glm::vec3(1.f, glm::linearRand(-1.f,5.f), 0.f));
		m_pShapeArray.push_back(pCube);
	}

	void Model::addRandomLine(){
		glm::vec3 startedPoint = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
		float size = 1.f;
		Line* pLine = new Line(m_pParticleManager, size, startedPoint);
		m_pShapeArray.push_back(pLine);
	}
}