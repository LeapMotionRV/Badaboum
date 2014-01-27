#ifndef LINE_H
#define LINE_H


#include "Shape.h"
#include "../ParticleManager.h"


namespace physical
{
	class Line : public Shape
	{
	public:
		Line(ParticleManager* pParticuleManager);

		void draw(physical::ParticleManager* pParticuleManager);

	private:
		glm::vec3		m_color;
		unsigned int	m_part1;
		unsigned int	m_part2;
		unsigned int	m_part3;
	};
}

#endif //CUBE_H