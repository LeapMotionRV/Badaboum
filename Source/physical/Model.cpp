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

		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.05f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));
		initParticleGround(20);
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

	void Model::initParticleGround(float size){
	m_pGround->addPolygonAndForce(
			glm::vec3(-size/2.f, 0.f, -size/2.f), glm::vec3(size/2.f, 0.f, -size/2.f), 
			glm::vec3(-size/2.f, 0.f, size/2.f), glm::vec3(size/2.f, 0.f, size/2.f), 
			glm::vec3(1.f, 1.f, 0.f), 1.f);
		for(int i=0; i<size; ++i){
			for(int j=0; j<size; ++j){
				m_pParticleManager->addParticle(glm::vec3(-size/2.f+0.5f+1.f*i, 1.f, -size/2.f+0.5f+1.f*j), glm::vec3(0.f, 0.f, 0.f), 7.f, glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
			}
		}
	}

	
	void Model::initGround(float size){
	m_pGround->addPolygonAndForce(
			glm::vec3(-size/2.f, 0.f, -size/2.f), glm::vec3(size/2.f, 0.f, -size/2.f), 
			glm::vec3(-size/2.f, 0.f, size/2.f), glm::vec3(size/2.f, 0.f, size/2.f), 
			glm::vec3(1.f, 1.f, 0.f), 1.f);
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

	void Model::addRandomLine(){
		glm::vec3 startedPoint = glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
		float size = 1.f;
		Line* pLine = new Line(m_pParticleManager, size, startedPoint);
		m_pShapeArray.push_back(pLine);
	}
}