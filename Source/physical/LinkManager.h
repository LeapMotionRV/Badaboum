#ifndef _IMAC3_LINKMANAGER_HPP
#define _IMAC3_LINKMANAGER_HPP


#include <vector>
#include <glm/glm.hpp>

#include "shapes\Link.h"

//#include "../render/ParticleRenderer.h"


namespace physical 
{
	class LinkManager {
	public:
		LinkManager(ParticleManager* pm);

		//getters
		std::vector<Link*> getLinkArray() const {return m_linkArray;}

		//add links and manipulate them
		void addLink(size_t idParticle1, size_t idParticle2);
		void addLinksForParticle(size_t idParticle);

		//draw
		void drawLinks();

	private:
		std::vector<Link*>	m_linkArray;
		ParticleManager*	m_pParticleManager;
		float				m_maxStepToCreateLink;
	};
}

#endif // IMAC3_LINKMANAGER_HPP
