#ifndef CUBE_H
#define CUBE_H


#include "Shape.h"
#include "../ParticleManager.h"
#include "../../util/LeapUtilGL.h"

namespace physical
{
	class Cube : public Shape
	{
	public:
		Cube(ParticleManager* pParticuleManager);
		~Cube();

		void drawCube(physical::ParticleManager* pParticuleManager);

	private:

		unsigned int m_part1;
		unsigned int m_part2;
		unsigned int m_part3;
		unsigned int m_part4;
		unsigned int m_part5;
		unsigned int m_part6;
		unsigned int m_part7;
		unsigned int m_part8;
	};
}

#endif //CUBE_H