#include <glm/gtc/random.hpp>
#include "../util/LeapUtilGL.h"

#include "ParticleManager.h"


namespace physical 
{
	const size_t	ParticleManager::s_nbStartedParticles = 5;
	const size_t	ParticleManager::s_nbEndedParticles = 5;
	const float		ParticleManager::s_massOfParticles = 1.f;
	const glm::vec3 ParticleManager::s_colorOfStartedParticles = glm::vec3(0.f, 0.f, 0.f); //blue
	const glm::vec3 ParticleManager::s_colorOfEndedParticles = glm::vec3(1.f, 0.8f, 0.f); //gold
	const glm::vec3 ParticleManager::s_colorOfParticles = glm::vec3(0.41f, 0.41f, 0.41f); //dimgrey

	ParticleManager::ParticleManager() {
		m_positionArray = std::vector<glm::vec3>();
		m_speedArray = std::vector<glm::vec3>();
		m_massArray = std::vector<float>();
		m_forceArray = std::vector<glm::vec3>();
		m_colorArray = std::vector<glm::vec3>();

		initFixedParticles();
	}

	void ParticleManager::initFixedParticles(){
		//started particles
		float fNbStartedParticles = static_cast<float>(s_nbStartedParticles);
		for(size_t i = 0; i < s_nbStartedParticles; ++i){
			addParticle(
				glm::vec3(glm::linearRand(-fNbStartedParticles/2.f, fNbStartedParticles/2.f), 0.1f, glm::linearRand(-fNbStartedParticles/2.f, fNbStartedParticles/2.f)), 
				glm::vec3(0.f, 0.f, 0.f), 
				ParticleManager::getMassOfParticles(), 
				glm::vec3(0.f, 0.f, 0.f), 
				ParticleManager::getColorOfStartedParticles());
		}
		//ending point
		float fNbEndedParticles = static_cast<float>(s_nbEndedParticles);
		for(size_t i = 0; i < s_nbEndedParticles; ++i){
			addParticle(
				glm::vec3(glm::linearRand(-fNbEndedParticles/2.f, fNbEndedParticles/2.f), 5.f, glm::linearRand(-fNbEndedParticles/2.f, fNbEndedParticles/2.f)), 
				glm::vec3(0.f, 0.f, 0.f), 
				ParticleManager::getMassOfParticles(), 
				glm::vec3(0.f, 0.f, 0.f), 
				ParticleManager::getColorOfEndedParticles());
		}
	}

	void ParticleManager::clear() {
		m_positionArray.clear();
		m_speedArray.clear();
		m_massArray.clear();
		m_forceArray.clear();
		m_colorArray.clear();
	}

	float ParticleManager::getHighestPosition() const {
		float highestPosition = -1.f;
		for(size_t i = 0; i < getNbParticles(); ++i) {
			if(highestPosition < 0.f || highestPosition < m_positionArray[i].y)
				highestPosition = m_positionArray[i].y;
		}
		return highestPosition;
	}

	unsigned int ParticleManager::addParticle(glm::vec3 pos, glm::vec3 speed, float mass, glm::vec3 force, glm::vec3 color) {
		m_positionArray.push_back(pos);
		m_speedArray.push_back(speed);
		m_massArray.push_back(mass);
		m_forceArray.push_back(force);
		m_colorArray.push_back(color);
		
		return m_positionArray.size() - 1;
	}

	void ParticleManager::addRandomParticles(unsigned int count){
		for(size_t i = 0; i < count; ++i) {
            addParticle(
				glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,10.f), glm::linearRand(-5.f,5.f)), 
				glm::vec3(0.f, 0.f, 0.f), 
				s_massOfParticles, 
				glm::vec3(0.f, 0.f, 0.f), 
				s_colorOfParticles);
        }
	}
	
	void ParticleManager::drawParticles() {
		if(m_positionArray.size() > 0){
			// draw each particles
			for(uint32_t i = 0; i < m_positionArray.size(); ++i) {
				LeapUtilGL::GLMatrixScope gridMatrixScope;
				glColor3f(m_colorArray[i].x, m_colorArray[i].y, m_colorArray[i].z);
				glTranslatef(m_positionArray[i].x,  m_positionArray[i].y, m_positionArray[i].z);
				LeapUtilGL::drawSphere(LeapUtilGL::eStyle::kStyle_Solid, m_massArray[i]);
			}
		}
    }
    
    void ParticleManager::move(float maxDist) {
        for(unsigned int i = 0; i < m_positionArray.size(); ++i) {
            m_positionArray[i] += glm::ballRand(maxDist);
        }
    }
    
    void ParticleManager::addForceToParticle(glm::vec3 force, size_t index){
    		m_forceArray[index] += force;
    }

    void ParticleManager::resetForceOfParticle(size_t index){
    		m_forceArray[index] = glm::vec3(0.f, 0.f, 0.f);
    }
}
