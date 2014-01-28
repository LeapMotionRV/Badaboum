#ifndef CUBE_H
#define CUBE_H


#include "Shape.h"
#include "../ParticleManager.h"

namespace physical
{
	class Cube : public Shape
	{
	public:
		Cube(ParticleManager* pParticuleManager, float size, glm::vec3 center, glm::vec3 color = glm::vec3(0.f, 0.f, 1.f));
		~Cube();

		//setters
		void setColor(glm::vec3 newColor){
			m_color = newColor;
		}

		//draw
		void draw(ParticleManager* pParticuleManager);

	private:
		glm::vec3		m_center;
		float			m_size;
		glm::vec3		m_color;

		//
		unsigned int	m_part1;
		unsigned int	m_part2;
		unsigned int	m_part3;
		unsigned int	m_part4;
		unsigned int	m_part5;
		unsigned int	m_part6;
		unsigned int	m_part7;
		unsigned int	m_part8;

		unsigned int	m_part_center1;//near face
		unsigned int	m_part_center2;//far face
		unsigned int	m_part_center3;//left face
		unsigned int	m_part_center4;//right face
		unsigned int	m_part_center5;//top face
		unsigned int	m_part_center6;//bottom face
	};
}

#endif //CUBE_H