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
		void reset();

		/**
		* Manage links
		*/
		void							addLink(size_t idParticle1, size_t idParticle2);
		void							addLinksForParticle(size_t idParticle);
		std::vector<Link*>::iterator	deleteLink(std::vector<Link*>::iterator itLink);
		void							deleteInvalidLinks(); //a link is invalid when the lenght > (2*m_maxLenghtToCreateLink)
		void							manageLinks(); //delete the invalid links, and create other necessary links

		/**
		* Forces
		*/
		void apply(float dt);

		/**
		* Draw
		*/
		void drawLinks();

		/**
		* Getters
		*/
		std::vector<Link*>	getLinkArray() const {return m_linkArray;}
		size_t				getNbLinkOfParticle(size_t idParticle) const ;
		ParticleManager*	getParticleManager() const {return m_pParticleManager;}
		float				getRigidity(){return Link::getRigidity();}
		float				getBrake(){return Link::getBrake();}
		bool				isLinkExist(size_t idParticle1, size_t idParticle2) const;
		bool				isLinkExistWithAStartedParticle() const;
		bool				isLinkExistWithAnEndedParticle() const;
		bool				isLinkExistFromAStartedParticleToAnEndedParticle() const;

		static const float	getMaxLenghtToCreateLink() {return s_maxLenghtToCreateLink;}
		static const size_t	getMaxLinksPerParticle() {return s_maxLinksPerParticle;}
		
		static glm::vec3	getColorOfLinks() {return s_colorOfLinks;}

		/**
		* Setters
		*/
		void setRigidity(float rigidity){Link::setRigidity(rigidity);}
		void setBrake(float brake){Link::setBrake(brake);}

		//suppress warning
		LinkManager & operator=( const LinkManager & ) {}

	private:
		std::vector<Link*>	m_linkArray;
		ParticleManager*	m_pParticleManager;
		
		static const float		s_maxLenghtToCreateLink;
		static const size_t		s_maxLinksPerParticle;
		static const glm::vec3	s_colorOfLinks;
	};
}

#endif // IMAC3_LINKMANAGER_HPP
