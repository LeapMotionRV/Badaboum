#ifndef CUBE_H
#define CUBE_H


#include "Shape.h"
#include "../ParticleManager.h"
#include "Facette.h"


namespace physical
{
	class Cube : public Shape
	{
	public:
		//construct
		Cube(ParticleManager* pParticuleManager, float size, glm::vec3 center, glm::vec3 color = glm::vec3(0.f, 0.f, 1.f));
		void addFacet(ParticleManager* pParticleManager, unsigned int firstPoint, unsigned int secondPoint, unsigned int thirdPoint);
		//forces
		void applyInternalForces(ParticleManager* pParticleManager, float dt);
		//draw
		void draw(ParticleManager* pParticuleManager);
		//void drawWithFacets(ParticleManager* pParticuleManager);
		//getters
		std::vector<Facette> getFacets(){return m_facets;}

	private:
		glm::vec3		m_center;
		float			m_size;
		glm::vec3		m_color;

		//lenght of springs
		glm::vec3 m_L0;//edges
		float m_L1;//diagonal of each face
		float m_L2;//little diagonals of each face
		float m_L3;//intern diagonals
		//rigidity
		float m_K0, m_K1, m_K2, m_K3;
		//brake
		float m_V0, m_V1, m_V2, m_V3;

		//id of particles
		//near face
		unsigned int	m_part1;
		unsigned int	m_part2;
		unsigned int	m_part3;
		unsigned int	m_part4;
		//far face
		unsigned int	m_part5;
		unsigned int	m_part6;
		unsigned int	m_part7;
		unsigned int	m_part8;
		//center of faces
		unsigned int	m_part_center1;//far face
		unsigned int	m_part_center2;//near face
		unsigned int	m_part_center3;//bottom face
		unsigned int	m_part_center4;//top face
		unsigned int	m_part_center5;//left face
		unsigned int	m_part_center6;//right face

		std::vector<Facette> m_facets;
	};
}

#endif //CUBE_H