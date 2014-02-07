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
		
		void applyInternalForces(ParticleManager* pParticleManager, float dt);
		void applyExternalForces(ParticleManager* pParticleManager, float dt);
		
		void draw(ParticleManager* pParticuleManager);

	private:
		float			m_size;
		glm::vec3		m_startedPoint;
		glm::vec3		m_color;

		//lenght of springs
		glm::vec3 m_L;
		//rigidity
		float m_K;
		//brake
		float m_V;

		//id of particles
		unsigned int	m_part1;
		unsigned int	m_part2;
		unsigned int	m_part3;
	};
}

#endif //LINE_H
