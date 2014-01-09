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
		inline std::vector<glm::vec3> getForceArray() const {return m_forceArray;}
		inline std::vector<glm::vec3> getSpeedArray() const {return m_speedArray;}
		inline std::vector<glm::vec3> getPositionArray() const {return m_positionArray;}
		inline std::vector<float> getMassArray() const {return m_massArray;}

		inline void setPositionOfParticle(glm::vec3 position, size_t index) {m_positionArray[index] = position;};
		inline void setSpeedOfParticle(glm::vec3 speed, size_t index) {m_speedArray[index] = speed;};
		inline void setForceOfParticle(glm::vec3 force, size_t index) {m_forceArray[index] = force;};

		unsigned int addParticle(glm::vec3 pos, glm::vec3 speed, float mass, glm::vec3 force, glm::vec3 color);
		void addRandomParticles(unsigned int count);

		void drawParticles(ParticleRenderer& renderer);
		void drawParticleGraph(ParticleGraph& graph, ParticleRenderer& renderer);
		
		void move(float maxDist);

		void addForceToParticle(glm::vec3 force, size_t index);
		void resetForceOfParticle(size_t index);
	private:
		std::vector<glm::vec3> m_positionArray;
		std::vector<glm::vec3> m_speedArray;
		std::vector<float> m_massArray;
		std::vector<glm::vec3> m_forceArray;
		std::vector<glm::vec3> m_colorArray;
	};

	struct ParticleState {
		glm::vec3 m_position;
		glm::vec3 m_speed;
	};

}

#endif // IMAC3_PARTICLEMANAGER_HPP
