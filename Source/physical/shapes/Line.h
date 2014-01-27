#ifndef LINE_H
#define LINE_H


#include "Shape.h"
#include "../ParticleManager.h"


namespace physical
{
	/**
		This shape describes a L.
	*/
	class Line : public Shape
	{
	public:
		Line(ParticleManager* pParticuleManager, float size, glm::vec3 startedPoint);

		void draw(ParticleManager* pParticuleManager);

	private:
		float			m_size;
		glm::vec3		m_startedPoint;
		glm::vec3		m_color;
		unsigned int	m_part1;
		unsigned int	m_part2;
		unsigned int	m_part3;
	};
}

#endif //LINE_H
