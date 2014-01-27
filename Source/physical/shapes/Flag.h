#ifndef _IMAC3_FLAG_HPP
#define _IMAC3_FLAG_HPP

#include "Shape.h"
#include "../ParticleManager.h"
#include <vector>
#include <glm/glm.hpp>

namespace physical{
	class Flag {

		public:
			Flag();
			~Flag();
			Flag(float mass, float width, float height, float depth, int gridWidth, int gridHeight, int gridDepth);

			glm::vec3 hookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2);
			glm::vec3 brakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2);
			void applyInternalForces(float dt);
			void update(float dt);
			ParticleManager getFlagParticles();

		private:
			//manager dedicated to the flag
			ParticleManager m_flagParticles;
			//number of Particles in width and height
			unsigned int m_gridWidth, m_gridHeight, m_gridDepth; // Dimensions de la grille de points

			//longueurs à vide 
			glm::vec2 m_L0; //topologie simple horizontal/vertical
			float m_L1;//topologie diagonale
			glm::vec2 m_L2;//topologie "saut de particule"

			float m_K0, m_K1, m_K2; // Paramètres de résistance
			float m_V0, m_V1, m_V2; // Paramètres de frein
	};
}
#endif // IMAC3_FLAG_HPP