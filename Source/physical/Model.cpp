#include <glm/gtc/random.hpp>
#include <string>

#include "Model.h"

namespace physical 
{
	Model::Model(unsigned int countParticles)
	{
		m_pLeapfrogSolver = new LeapfrogSolver();

		//data of the scene
		m_pParticleManager =  new ParticleManager();
		m_pLinkManager = new LinkManager(m_pParticleManager);
		
		m_pGround = new Ground(m_pLeapfrogSolver);
		initGround(m_pParticleManager->getNbFixedParticles() * 2);
		initParticleGround(m_pParticleManager->getNbFixedParticles());

		//forces
		m_pGravity = new ConstantForce(glm::vec3(0.f, -0.05f, 0.f));
		m_pWind = new ConstantForce(glm::vec3(0.02f, -0.01f, 0.f));
	}

	Model::~Model(){
		delete m_pLeapfrogSolver;
		delete m_pParticleManager;
		delete m_pLinkManager;
		delete m_pGravity;
		delete m_pWind;
		delete m_pGround;
	}

	void Model::initParticleGround(float size){
		for(int i=0; i<size; ++i){
			for(int j=0; j<size; ++j){
				float mass = 1.f;
				if (i == 1 && i == j)
					mass = 5.f;
				m_pParticleManager->addParticle(glm::vec3(-size/2.f+0.5f+1.f*i, 1.f, -size/2.f+0.5f+1.f*j), glm::vec3(0.f, 0.f, 0.f), mass, glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
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
			m_pLinkManager->apply(dt);
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticle(){
		glm::vec3 position = glm::vec3(glm::linearRand(-2.f,2.f), glm::linearRand(0.f,5.f), glm::linearRand(-2.f,2.f));
		glm::vec3 speed = glm::vec3(0.f, 0.f, 0.f);
		float mass = 1.f;
		glm::vec3 force = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 color = glm::vec3(glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f));
		unsigned int idParticle = m_pParticleManager->addParticle(position, speed, mass, force, color);

		m_pLinkManager->addLinksForParticle(idParticle);
	}

	void Model::addParticleWhereLeapIs(glm::vec3 pos){
		unsigned int idParticle = m_pParticleManager->addParticleWhereLeapIs(pos);
		m_pLinkManager->addLinksForParticle(idParticle);
	}

}