#ifndef CUBE_H
#define CUBE_H


#include "../ParticleManager.h"
#include "../../util/LeapUtilGL.h"

namespace physical
{
	class Cube
	{
	public:
		Cube(ParticleManager* pParticuleManager);
		~Cube();

		void drawCube(physical::ParticleManager* pParticuleManager);

		//getter
		const ParticleGraph* getCubeGraph(){return m_cubeGraph;}

	private:
		ParticleGraph* m_cubeGraph;

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