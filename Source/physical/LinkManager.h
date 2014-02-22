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

		//add links and manipulate them
		void addLink(size_t idParticle1, size_t idParticle2);
		void addLinksForParticle(size_t idParticle);
		void deleteLink(int idLink);

		//forces
		void apply(float dt);

		//draw
		void drawLinks();

		//getters
		std::vector<Link*> getLinkArray() const {return m_linkArray;}
		float getRigidity(){return Link::getRigidity();}
		float getBrake(){return Link::getBrake();}

		//setters
		void setRigidity(float rigidity){Link::setRigidity(rigidity);}
		void setBrake(float brake){Link::setBrake(brake);}

	private:
		std::vector<Link*>	m_linkArray;
		ParticleManager*	m_pParticleManager;
		const float			m_maxStepToCreateLink;
	};
}

#endif // IMAC3_LINKMANAGER_HPP
