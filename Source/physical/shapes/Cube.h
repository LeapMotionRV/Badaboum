#ifndef CUBE_H
#define CUBE_H


#include "../ParticleManager.h"


namespace physical
{
	class Cube
	{
	public:
		Cube(ParticleManager* pParticuleManager);
		~Cube();

		//getter
		const ParticleGraph* getCubeGraph(){return m_cubeGraph;}

	private:
		ParticleGraph* m_cubeGraph;
	};
}

#endif //CUBE_H