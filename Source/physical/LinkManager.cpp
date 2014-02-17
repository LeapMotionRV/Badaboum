#include "LinkManager.h"


namespace physical 
{
	LinkManager::LinkManager(ParticleManager* pm):m_maxStepToCreateLink(3.f)
	{
		m_linkArray = std::vector<Link*>();
		m_pParticleManager = pm;
	}

	void LinkManager::addLink(size_t idParticle1, size_t idParticle2){
		m_linkArray.push_back(new Link(m_pParticleManager, idParticle1, idParticle2));
	}

	void LinkManager::addLinksForParticle(size_t idParticle){
		glm::vec3 particleToAddLinksPosition = m_pParticleManager->getPosition(idParticle);

		//looking for links near the particle
		for(size_t currentIdParticle = 0; currentIdParticle < m_pParticleManager->getPositionArray().size(); currentIdParticle++){
			glm::vec3 currentParticlePosition = m_pParticleManager->getPosition(currentIdParticle);
			glm::vec3 vectorDistance = particleToAddLinksPosition - currentParticlePosition;
			if(vectorDistance.x < m_maxStepToCreateLink && 
				vectorDistance.y < m_maxStepToCreateLink &&
				vectorDistance.z < m_maxStepToCreateLink){
					addLink(idParticle, currentIdParticle);
			}
		}
	}

	void LinkManager::apply(float dt){
		for(size_t i = 0; i < m_linkArray.size(); ++i){
			m_linkArray[i]->applyExternalForces(m_pParticleManager, dt);
			m_linkArray[i]->applyInternalForces(m_pParticleManager, dt);
		}
	}

	void LinkManager::drawLinks(){
		for(size_t i = 0; i < m_linkArray.size(); i++){
			m_linkArray[i]->draw(m_pParticleManager);
		}
	}
}
