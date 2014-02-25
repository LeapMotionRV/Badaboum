#ifndef _IMAC3_LINKMANAGER_HPP
#define _IMAC3_LINKMANAGER_HPP

#include <vector>
#include <glm/glm.hpp>

#include "ParticleManager.h"
#include "shapes/Link.h"

namespace physical 
{
	class LinkManager {
	public:
		LinkManager(ParticleManager* pm);

		//suppress warning
		LinkManager & operator=( const LinkManager & ) {}

		//add links and manipulate them
		void							addLink(size_t idParticle1, size_t idParticle2);
		void							addLinksForParticle(size_t idParticle);
		std::vector<Link*>::iterator	deleteLink(std::vector<Link*>::iterator itLink);
		//a link is invalid when the lenght is superior of m_maxStepToCreateLink
		void							deleteInvalidLinks();

		//forces
		void apply(float dt);

		//draw
		void drawLinks();

		//getters
		std::vector<Link*>	getLinkArray() const {return m_linkArray;}
		ParticleManager*	getParticleManager() const {return m_pParticleManager;}
		const float			getMaxStepToCreateLink() const {return m_maxStepToCreateLink;}
		float				getRigidity(){return Link::getRigidity();}
		float				getBrake(){return Link::getBrake();}

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
