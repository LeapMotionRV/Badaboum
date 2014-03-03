#include "LinkManager.h"
#include <windows.h>


namespace physical 
{
	const float		LinkManager::s_maxLenghtToCreateLink = 2.f;
	const size_t	LinkManager::s_maxLinksPerParticle = 8;
	const glm::vec3	LinkManager::s_colorOfLinks = glm::vec3(0.97f, 0.97f, 1.f); //ghostwhite

	LinkManager::LinkManager(ParticleManager* pm){
		m_linkArray = std::vector<Link*>();
		m_pParticleManager = pm;
	}

	void LinkManager::clear() {
		m_linkArray.clear();
	}

	void LinkManager::addLink(size_t idParticle1, size_t idParticle2){
		m_linkArray.push_back(new Link(m_pParticleManager, idParticle1, idParticle2));
	}

	void LinkManager::addLinksForParticle(size_t idParticle){
		if(m_pParticleManager->isFixedParticle(idParticle))
			return;
		if(getNbLinkOfParticle(idParticle) >= s_maxLinksPerParticle)
			return;

		glm::vec3 particleToAddLinksPosition = m_pParticleManager->getPosition(idParticle);

		//fill with -1 => correspond to no possible idParticle
		int nearestParticles[s_maxLinksPerParticle] = {};
		std::fill(nearestParticles, nearestParticles + s_maxLinksPerParticle, -1);

		//fill the table nearestParticles
		for(size_t currentIdParticle = 0; currentIdParticle < m_pParticleManager->getPositionArray().size(); currentIdParticle++){
			//no link between particle itself
			if(currentIdParticle == idParticle)
				continue;
			if(isLinkExist(idParticle, currentIdParticle))
				continue;
			//check lenght
			glm::vec3 currentParticlePosition = m_pParticleManager->getPosition(currentIdParticle);
			glm::vec3 currentVector = particleToAddLinksPosition - currentParticlePosition;
			if(glm::length(currentVector) > s_maxLenghtToCreateLink)
				continue;

			bool idCurrentParticleAdded = false;

			//if the array of nearest particle is not full
			for(size_t i = 0; i < s_maxLinksPerParticle; ++i) {
				if(nearestParticles[i] == -1){
					nearestParticles[i] = currentIdParticle;
					idCurrentParticleAdded = true;
					break;
				}
			}
			//if the current particle is still not added
			//find which particle in the table of nearest is the more distant from the one tested
			if(!idCurrentParticleAdded){
				int indexOfMoreDistantParticleInNearestParticleTable = -1;
				float lenghtOfMoreDistantParticleInNearestParticleTable = -1.f;
				for(size_t i = 0; i < s_maxLinksPerParticle; ++i) {
					glm::vec3 oneOfNearestParticlePosition = m_pParticleManager->getPosition(nearestParticles[i]);
					glm::vec3 testedVector = particleToAddLinksPosition - oneOfNearestParticlePosition;
				
					if(lenghtOfMoreDistantParticleInNearestParticleTable < 0.f){
						indexOfMoreDistantParticleInNearestParticleTable = i;
						lenghtOfMoreDistantParticleInNearestParticleTable = glm::length(testedVector);
					}
					else if(lenghtOfMoreDistantParticleInNearestParticleTable < glm::length(testedVector)){
						indexOfMoreDistantParticleInNearestParticleTable = i;
						lenghtOfMoreDistantParticleInNearestParticleTable = glm::length(testedVector);
					}
				}
				//we know yet the index of the particle in nearestParticle table which is the more distant of the particle tested
				//we test now if the distance between the particleTested and the current one in the loop on all particles is closer than this one distant
				glm::vec3 distantParticlePosition = m_pParticleManager->getPosition(nearestParticles[indexOfMoreDistantParticleInNearestParticleTable]);
				glm::vec3 longestVector = particleToAddLinksPosition - distantParticlePosition;

				//if it's the case we have to replace the index of particle in nearestParticles with the index of the currentParticle in the loop
				if( glm::length(currentVector) < glm::length(longestVector) ){
					nearestParticles[indexOfMoreDistantParticleInNearestParticleTable] = currentIdParticle;
				}
			}
		}
		//now we have our table of nearestParticle filled in
		for(size_t i = 0; i < s_maxLinksPerParticle; ++i){
			if(nearestParticles[i] >= 0){
				//check if both of particle can have a new link
				if((getNbLinkOfParticle(idParticle) < s_maxLinksPerParticle) && (getNbLinkOfParticle(nearestParticles[i]) < s_maxLinksPerParticle)){
					addLink(idParticle, nearestParticles[i]);
				}
			}
		}
	}

	std::vector<Link*>::iterator LinkManager::deleteLink(std::vector<Link*>::iterator itLink){
		return m_linkArray.erase(itLink);
	}

	void LinkManager::deleteInvalidLinks() {
		for (std::vector<Link*>::iterator it = m_linkArray.begin(); it != m_linkArray.end();) {
			bool isValid = (*it)->isValid(m_pParticleManager);
			if(!isValid)
				it = deleteLink(it);
			else 
				++it;
		 }
	}

	void LinkManager::manageLinks() {
		deleteInvalidLinks();
		for(size_t idParticle = 0; idParticle < m_pParticleManager->getPositionArray().size(); ++idParticle){
			addLinksForParticle(idParticle);
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

	size_t LinkManager::getNbLinkOfParticle(size_t idParticle) const {
		size_t nbLinkOfParticle = 0;
		for(size_t idLink = 0; idLink < m_linkArray.size(); ++idLink){
			size_t idParticle1 = m_linkArray[idLink]->getGraph()[0][0].first;
			size_t idParticle2 = m_linkArray[idLink]->getGraph()[0][0].second;
			
			if(idParticle == idParticle1)
				nbLinkOfParticle++;
			else if(idParticle == idParticle2)
				nbLinkOfParticle++;
		}
		return nbLinkOfParticle;
	}

	bool LinkManager::isLinkExist(size_t idParticle1, size_t idParticle2) const {
		for(size_t idLink = 0; idLink < m_linkArray.size(); ++idLink){
			size_t linkIdParticle1 = m_linkArray[idLink]->getGraph()[0][0].first;
			size_t linkIdParticle2 = m_linkArray[idLink]->getGraph()[0][0].second;

			if((linkIdParticle1 == idParticle1 && linkIdParticle2 == idParticle2)
				|| (linkIdParticle1 == idParticle2 && linkIdParticle2 == idParticle1))
				return true;
		}
		return false;
	}

	
	bool LinkManager::isLinkExistWithAStartedParticle() const{
		for(size_t idLink = 0; idLink < m_linkArray.size(); ++idLink){
			size_t idParticle1 = m_linkArray[idLink]->getGraph()[0][0].first;
			size_t idParticle2 = m_linkArray[idLink]->getGraph()[0][0].second;

			if((m_pParticleManager->isStartedParticle(idParticle1) && !m_pParticleManager->isFixedParticle(idParticle2))
				|| (m_pParticleManager->isStartedParticle(idParticle2) && !m_pParticleManager->isFixedParticle(idParticle1)))
				return true;
		}
		return false;
	}

	bool LinkManager::isLinkExistWithAnEndedParticle() const{
		for(size_t idLink = 0; idLink < m_linkArray.size(); ++idLink){
			size_t idParticle1 = m_linkArray[idLink]->getGraph()[0][0].first;
			size_t idParticle2 = m_linkArray[idLink]->getGraph()[0][0].second;

			if((m_pParticleManager->isEndedParticle(idParticle1) && !m_pParticleManager->isFixedParticle(idParticle2))
				|| (m_pParticleManager->isEndedParticle(idParticle2) && !m_pParticleManager->isFixedParticle(idParticle1)))
				return true;
		}
		return false;
	}

	bool LinkManager::isPathExistFromAStartedParticleToAnEndedParticle() const {
		return (isLinkExistWithAStartedParticle() && isLinkExistWithAnEndedParticle()) ? true : false;
	}
}
