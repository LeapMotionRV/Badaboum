#include "LinkManager.h"
#include <windows.h>


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

		const int numberOfLinksToCreate = 4;
		//table containing indexes of nearest particles of the particle tested, we have to fill it
		int nearestParticles[numberOfLinksToCreate] = {0};

		//fill the table nearestParticles with the nearest particles to the one tested, warning to not test with the particle itself (this is why size - 1)
		for(size_t currentIdParticle = 0; currentIdParticle < m_pParticleManager->getPositionArray().size() - 1; currentIdParticle++){
			glm::vec3 currentParticlePosition = m_pParticleManager->getPosition(currentIdParticle);
			glm::vec3 currentVector = particleToAddLinksPosition - currentParticlePosition;

			//index of the particle from nearestParticles which is the more distant from the one tested
			int indexOfMoreDistantParticleInNearestParticleTable = 0;

			//find which particle of the table of nearest is the more distant from the one tested
			for(size_t i = 0; i < numberOfLinksToCreate; ++i){
				glm::vec3 oneOfNearestParticlePosition = m_pParticleManager->getPosition(nearestParticles[i]);
				glm::vec3 testedVector = particleToAddLinksPosition - oneOfNearestParticlePosition;
				glm::vec3 distantParticlePosition = m_pParticleManager->getPosition(nearestParticles[indexOfMoreDistantParticleInNearestParticleTable]);
				glm::vec3 maybeLongestVector = particleToAddLinksPosition - distantParticlePosition;
				
				if(glm::length(maybeLongestVector) < glm::length(testedVector)){
					indexOfMoreDistantParticleInNearestParticleTable = i;
				}
			}
			//we know yet the index of the particle in nearestParticle table which is the more distant of the particle tested
			//we test know if the distance between the particleTested and the current one in the loop on all particles is closer than this one distant
			glm::vec3 distantParticlePosition = m_pParticleManager->getPosition(nearestParticles[indexOfMoreDistantParticleInNearestParticleTable]);
			glm::vec3 longestVector = particleToAddLinksPosition - distantParticlePosition;

			//if it's the case we have to replace the index of particle in nearestParticles with the index of the currentParticle in the loop
			if( glm::length(currentVector) < glm::length(longestVector) ){
				nearestParticles[indexOfMoreDistantParticleInNearestParticleTable] = currentIdParticle;
			}
		}
		//now we have our table of nearestParticle fill in
		//we create the links between these nearest particles and the one tested
		for(size_t i = 0; i < numberOfLinksToCreate; ++i){
			//we look the length, if it is inferior to 1 we don't create it
			glm::vec3 currentParticlePosition = m_pParticleManager->getPosition(nearestParticles[i]);
			glm::vec3 actualVector = particleToAddLinksPosition - currentParticlePosition;
			int maximumLengthToCreateLink = 5;
			if(glm::length(actualVector) < maximumLengthToCreateLink){
				addLink(idParticle, nearestParticles[i]);
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

	void LinkManager::deleteLink(int idLink){
		delete m_linkArray[idLink];
		m_linkArray.erase(m_linkArray.begin()+idLink-1);
	}
}
