#include <glm/gtc/random.hpp>
#include <string>

#include "Model.h"

namespace physical 
{
	Model::Model(unsigned int countParticles) : m_nbMaxParticle(100), m_nbHumanInitial(7000000000){
		m_bIsApplicationStarted = true;
		
		m_bIsPlayerWin = false;
		m_bIsPlayerLoose = false;

		m_pLeapfrogSolver = new LeapfrogSolver();

		//data of the scene
		m_pParticleManager =  new ParticleManager();
		m_pLinkManager = new LinkManager(m_pParticleManager);
		m_pParticleManager->addRandomParticles(countParticles);
		
		m_pGround = new Ground(m_pLeapfrogSolver);
		//initGround changes the size of the ground, but the texture repetition is managed in draw function of Ground
		initGround(100);//initGround(10*ParticleManager::getNbStartedParticles());

		//forces
		m_constantForceArray = std::vector<ConstantForce*>();
		m_constantForceArray.push_back(new ConstantForce(glm::vec3(0.f, -0.05f, 0.f))); //-0.9 (trop fort ptet)

		//human data
		m_nbHumanLeft = m_nbHumanInitial;
		m_previousParticleNb = 0;
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

	void Model::initGround(const size_t size){;
		float fSize = static_cast<float>(size);
		m_pGround->addPolygonAndForce(
			glm::vec3(-fSize, 0.f, -fSize), glm::vec3(-fSize, 0.f, fSize), 
			glm::vec3(fSize, 0.f, fSize), glm::vec3(fSize, 0.f, -fSize), 
			glm::vec3(1.f, 1.f, 0.f), 1.f);
	}

	void Model::reset(){
		m_pLinkManager->clear();
		m_pParticleManager->clear();
		m_bIsPlayerWin = false;
		m_bIsPlayerLoose = false;
		m_nbHumanLeft = m_nbHumanInitial;
		m_previousParticleNb = 0;
		m_pParticleManager->initFixedParticles();
	}

	void Model::startSimulation(float dt) 
	{
		//the game
		if(m_pLinkManager->isPathExistFromAStartedParticleToAnEndedParticle() && !m_bIsPlayerLoose){
			m_bIsPlayerWin = true;
		}
		if(m_nbHumanLeft <= 0){
			m_bIsPlayerLoose = true;
		}
		//links
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
		m_pParticleManager->addParticle(
			pos, 
			glm::vec3(0.f, 0.f, 0.f), 
			ParticleManager::getMassOfParticles(), 
			glm::vec3(0.f, 0.f, 0.f), 
			ParticleManager::getColorOfParticles());
	}

	bool Model::isApplicationStarted() const {
		return m_bIsApplicationStarted;
	}

	bool Model::isPlayerWin() const {
		return m_bIsPlayerWin;
	}

	bool Model::isPlayerLoose() const {
		return m_bIsPlayerLoose;
	}
}