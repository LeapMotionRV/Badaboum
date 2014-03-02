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
		void							deleteInvalidLinks(); //a link is invalid when the lenght > (2*m_maxLenghtToCreateLink)
		void							manageLinks(); //delete the invalid links, and create other necessary links

		//forces
		void apply(float dt);

		//draw
		void drawLinks();

		//getters
		std::vector<Link*>	getLinkArray() const {return m_linkArray;}
		size_t				getNbLinkOfParticle(size_t idParticle) const ;
		ParticleManager*	getParticleManager() const {return m_pParticleManager;}
		static const float	getMaxLenghtToCreateLink() {return m_maxLenghtToCreateLink;}
		static const size_t	getMaxLinksPerParticle() {return m_maxLinksPerParticle;}
		float				getRigidity(){return Link::getRigidity();}
		float				getBrake(){return Link::getBrake();}
		bool				isLinkAlreadyExist(size_t idParticle1, size_t idParticle2) const;
		
		static glm::vec3	getColorOfLinks() {return s_colorOfLinks;}

		//setters
		void setRigidity(float rigidity){Link::setRigidity(rigidity);}
		void setBrake(float brake){Link::setBrake(brake);}

	private:
		std::vector<Link*>	m_linkArray;
		ParticleManager*	m_pParticleManager;
		static const float	m_maxLenghtToCreateLink;
		static const size_t m_maxLinksPerParticle;
		
		static const glm::vec3	s_colorOfLinks;
	};
}

#endif // IMAC3_LINKMANAGER_HPP
