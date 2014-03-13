#ifndef _IMAC3_PARTICLEMANAGER_HPP
#define _IMAC3_PARTICLEMANAGER_HPP

#include <vector>
#include <glm/glm.hpp>

namespace physical 
{
	typedef std::vector<std::pair<unsigned int, unsigned int>> ParticleGraph;

	class ParticleManager {
	public:
		ParticleManager();
		void initFixedParticles();
		void clear();

		/**
		* Manage particles
		*/
		unsigned int	addParticle(glm::vec3 pos, glm::vec3 speed, float mass, glm::vec3 force, glm::vec3 color);//return index of particle
		void			addRandomParticles(unsigned int count);
		void			addForceToParticle(glm::vec3 force, size_t index);
		void			resetForceOfParticle(size_t index);
		void			move(float maxDist);

		/**
		* Draw
		*/
		void drawParticles();

		/**
		* Getters
		*/
		std::vector<glm::vec3>	getForceArray() const {return m_forceArray;}
		std::vector<glm::vec3>	getSpeedArray() const {return m_speedArray;}
		std::vector<glm::vec3>	getPositionArray() const {return m_positionArray;}
		std::vector<float>		getMassArray() const {return m_massArray;}
		const unsigned int		getNbParticles() const {return m_positionArray.size();}
		float					getHighestPosition() const;
		unsigned int			getNbPlayerParticles(){return m_positionArray.size() - s_nbStartedParticles - s_nbEndedParticles;}
		
		static const size_t		getNbStartedParticles() {return s_nbStartedParticles;}
		static const size_t		getNbEndedParticles() {return s_nbEndedParticles;}
		static float			getMassOfParticles() {return s_massOfParticles;}
		static glm::vec3		getColorOfStartedParticles() {return s_colorOfStartedParticles;}
		static glm::vec3		getColorOfEndedParticles() {return s_colorOfEndedParticles;}
		static glm::vec3		getColorOfParticles() {return s_colorOfParticles;}

		glm::vec3 getPosition(int idParticule) const { return m_positionArray[idParticule]; }
		glm::vec3 getVelocity(int idParticule) const { return m_speedArray[idParticule]; }

		bool isStartedParticle(size_t idParticle) {return (idParticle < s_nbStartedParticles) ? true : false;}
		//started particle and ended particle are at the beginning of the table
		bool isEndedParticle(size_t idParticle) {return (idParticle > s_nbStartedParticles && idParticle < (s_nbStartedParticles+s_nbEndedParticles)) ? true : false;}
		bool isFixedParticle(size_t idParticle) {return (idParticle < (s_nbStartedParticles+s_nbEndedParticles)) ? true : false;}

		/**
		* Setters
		*/
		void setPositionOfParticle(glm::vec3 position, size_t index) {m_positionArray[index] = position;};
		void setSpeedOfParticle(glm::vec3 speed, size_t index) {m_speedArray[index] = speed;};
		void setForceOfParticle(glm::vec3 force, size_t index) {m_forceArray[index] = force;};

		//suppress warning
		ParticleManager & operator=( const ParticleManager & ) {}
		
	private:
		std::vector<glm::vec3>	m_positionArray;
		std::vector<glm::vec3>	m_speedArray;
		std::vector<float>		m_massArray;
		std::vector<glm::vec3>	m_forceArray;
		std::vector<glm::vec3>	m_colorArray;
		
		//a started or an ended particle is always a fixed particle
		static const size_t		s_nbStartedParticles; //the first set of partciles in the array of particles
		static const size_t		s_nbEndedParticles; //the second set of particles in the array of particles

		static const float		s_massOfParticles;
		static const glm::vec3	s_colorOfStartedParticles;
		static const glm::vec3	s_colorOfEndedParticles;
		static const glm::vec3	s_colorOfParticles;
	};

	struct ParticleState {
		glm::vec3 m_position;
		glm::vec3 m_speed;
	};
}

#endif // IMAC3_PARTICLEMANAGER_HPP
