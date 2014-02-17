#include "LinkManager.h"


namespace physical 
{
	LinkManager::LinkManager(ParticleManager* pm){
		m_linkArray = std::vector<Link*>();
		m_pParticleManager = pm;
		m_maxStepToCreateLink = 5.f;
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

	void LinkManager::drawLinks(){
		for(size_t linkId = 0; linkId < m_linkArray.size(); linkId++){
			m_linkArray[linkId]->draw(m_pParticleManager);
		}
	}
}
