#include <glm/gtc/random.hpp>
#include <string>

#include "Model.h"

namespace physical 
{
	Model::Model(unsigned int countParticles) :  m_nbMaxParticle(100)
	{
		m_pLeapfrogSolver = new LeapfrogSolver();

		//data of the scene
		m_pParticleManager =  new ParticleManager();
		m_pLinkManager = new LinkManager(m_pParticleManager);
		m_pParticleManager->addRandomParticles(countParticles);
		
		m_pGround = new Ground(m_pLeapfrogSolver);
		initGround(m_pParticleManager->getNbFixedParticles() * 2);

		//forces
		m_constantForceArray = std::vector<ConstantForce*>();
		 //gravity
		m_gravity = new ConstantForce(glm::vec3(0.f, -0.05f, 0.f));
		m_constantForceArray.push_back(m_gravity);
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

	void Model::initGround(const unsigned int size){;
		float fSize = -static_cast<float>(size);
		m_pGround->addPolygonAndForce(
			glm::vec3(-fSize/2.f, 0.f, -fSize/2.f), glm::vec3(fSize/2.f, 0.f, -fSize/2.f), 
			glm::vec3(-fSize/2.f, 0.f, fSize/2.f), glm::vec3(fSize/2.f, 0.f, fSize/2.f), 
			glm::vec3(1.f, 1.f, 0.f), 1.f);
	}

	void Model::startSimulation(float dt) 
	{
		m_pLinkManager->manageLinks();
		//apply forces
		if(dt != 0) {
			for(unsigned int i = 0; i < m_constantForceArray.size(); ++i){
				m_constantForceArray[i]->apply(m_pParticleManager);
			}
			m_pGround->apply(m_pParticleManager, dt);
			m_pLinkManager->apply(dt);
		}
		//solve physics
		m_pLeapfrogSolver->solve(m_pParticleManager, dt);
	}

	void Model::addRandomParticles(unsigned int count){
		m_pParticleManager->addRandomParticles(count);
	}

	void Model::addParticleWhereLeapIs(glm::vec3 pos){
		unsigned int idParticle = m_pParticleManager->addParticle(
			pos, 
			glm::vec3(0.f, 0.f, 0.f), 
			ParticleManager::getMassOfParticles(), 
			glm::vec3(0.f, 0.f, 0.f), 
			glm::vec3(glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f)));
	}

}