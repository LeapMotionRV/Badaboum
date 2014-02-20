#ifndef _IMAC3_PARTICLEMANAGER_HPP
#define _IMAC3_PARTICLEMANAGER_HPP


#include <vector>
#include <glm/glm.hpp>

#include "../render/ParticleRenderer.h"


namespace physical 
{
	typedef std::vector<std::pair<unsigned int, unsigned int>> ParticleGraph;

	class ParticleManager {
	public:
		ParticleManager();
		void initFixedParticles(float size);

		//getters
		std::vector<glm::vec3>	getForceArray() const {return m_forceArray;}
		std::vector<glm::vec3>	getSpeedArray() const {return m_speedArray;}
		std::vector<glm::vec3>	getPositionArray() const {return m_positionArray;}
		std::vector<float>		getMassArray() const {return m_massArray;}
		const unsigned int		getNbParticles() const {return m_positionArray.size();}
		const unsigned int		getNbFixedParticles() const {return m_nbFixedParticles;}
		
		glm::vec3 getPosition(int idParticule) const { return m_positionArray[idParticule]; }
		glm::vec3 getVelocity(int idParticule) const { return m_speedArray[idParticule]; }

		bool isFixedParticle(size_t idParticle) {return (idParticle < m_nbFixedParticles*m_nbFixedParticles) ? true : false;}

		//setters
		void setPositionOfParticle(glm::vec3 position, size_t index) {m_positionArray[index] = position;};
		void setSpeedOfParticle(glm::vec3 speed, size_t index) {m_speedArray[index] = speed;};
		void setForceOfParticle(glm::vec3 force, size_t index) {m_forceArray[index] = force;};

		//add particles and manipulate them
		unsigned int	addParticle(glm::vec3 pos, glm::vec3 speed, float mass, glm::vec3 force, glm::vec3 color);//return index of particle
		void			addRandomParticles(unsigned int count);
		void			addForceToParticle(glm::vec3 force, size_t index);
		void			resetForceOfParticle(size_t index);
		void			move(float maxDist);

		//draw
		void drawParticles(render::ParticleRenderer& renderer);
		
	private:
		std::vector<glm::vec3>	m_positionArray;
		std::vector<glm::vec3>	m_speedArray;
		std::vector<float>		m_massArray;
		std::vector<glm::vec3>	m_forceArray;
		std::vector<glm::vec3>	m_colorArray;
		const unsigned int		m_nbFixedParticles;
	};

	struct ParticleState {
		glm::vec3 m_position;
		glm::vec3 m_speed;
	};
}

#endif // IMAC3_PARTICLEMANAGER_HPP
