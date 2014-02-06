#include <glm/gtc/random.hpp>

#include "ParticleManager.h"


namespace physical 
{
	ParticleManager::ParticleManager(){
		m_positionArray = std::vector<glm::vec3>();
		m_speedArray = std::vector<glm::vec3>();
		m_massArray = std::vector<float>();
		m_forceArray = std::vector<glm::vec3>();
		m_colorArray = std::vector<glm::vec3>();
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
			glm::vec3 position = glm::vec3(1.2f, glm::linearRand(-1.f,5.f), 0.f);//glm::vec3(glm::linearRand(-5.f,5.f), glm::linearRand(0.f,5.f), glm::linearRand(-5.f,5.f));
			glm::vec3 speed = glm::vec3(0.f, 0.f, 0.f);
			glm::vec3 force = glm::vec3(0.f, 0.f, 0.f);
			glm::vec3 color = glm::vec3(glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f),glm::linearRand(0.f,1.f));
            addParticle(position, speed, glm::linearRand(0.01f,0.5f), force, color);
        }
	}
	
	void ParticleManager::drawParticles(render::ParticleRenderer& renderer) {
		if(m_positionArray.size() > 0){
			renderer.drawParticles(m_positionArray.size(),
							&m_positionArray[0],
							&m_massArray[0],
							&m_colorArray[0]);
		}
    }

	/*void ParticleManager::drawParticleGraph(const ParticleGraph* graph, render::ParticleRenderer& renderer){
    	renderer.drawLines(graph->size(),
                   graph,
                   m_positionArray.size(),
                   &m_positionArray[0],
                   &m_colorArray[0],
                   1.f);
    }*/
    
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
