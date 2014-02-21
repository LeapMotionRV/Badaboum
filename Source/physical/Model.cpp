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
		m_pParticleManager->initFixedParticles(m_pParticleManager->getNbFixedParticles());
		m_pLinkManager = new LinkManager(m_pParticleManager);
		
		m_pGround = new Ground(m_pLeapfrogSolver);
		initGround(m_pParticleManager->getNbFixedParticles() * 2);

		//forces
		m_constantForceArray = std::vector<ConstantForce*>();
		m_constantForceArray.push_back(new ConstantForce(glm::vec3(0.f, -0.05f, 0.f))); //gravity
	}

	Model::~Model(){
		delete m_pLeapfrogSolver;
		delete m_pParticleManager;
		delete m_pLinkManager;
		delete m_pGround;
		for(std::vector<ConstantForce*>::iterator it = m_constantForceArray.begin(); it != m_constantForceArray.end(); ){
			it = m_constantForceArray.erase(it);
		}
	}

	void Model::initGround(const unsigned int size){
		m_pGround->addPolygonAndForce(
				glm::vec3(-size/2.f, 0.f, -size/2.f), glm::vec3(size/2.f, 0.f, -size/2.f), 
				glm::vec3(-size/2.f, 0.f, size/2.f), glm::vec3(size/2.f, 0.f, size/2.f), 
				glm::vec3(1.f, 1.f, 0.f), 1.f);
	}

	void Model::startSimulation(float dt) 
	{
		if(dt != 0) {
			for(unsigned int i = 0; i < m_constantForceArray.size(); ++i){
				m_constantForceArray[i]->apply(m_pParticleManager);
			}
			m_pGround->apply(m_pParticleManager, dt);
			m_pLinkManager->apply(dt);
		}
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticle(){
		unsigned int idParticle = m_pParticleManager->addParticle(
			glm::vec3(glm::linearRand(-2.f,2.f), glm::linearRand(0.f,5.f), glm::linearRand(-2.f,2.f)), 
			glm::vec3(0.f, 0.f, 0.f), 
			1.f, 
			glm::vec3(0.f, 0.f, 0.f), 
			glm::vec3(glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f)));
		m_pLinkManager->addLinksForParticle(idParticle);
	}

	void Model::addParticleWhereLeapIs(glm::vec3 pos){
		unsigned int idParticle = m_pParticleManager->addParticle(
			pos, 
			glm::vec3(0.f, 0.f, 0.f), 
			1.f, 
			glm::vec3(0.f, 0.f, 0.f), 
			glm::vec3(glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f)));
		m_pLinkManager->addLinksForParticle(idParticle);
	}

}