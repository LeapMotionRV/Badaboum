#ifndef CUBE_H
#define CUBE_H

#include "../physical/ParticleManager.h"

class Cube
{
private:
		physical::ParticleGraph		m_cubeGraph;

public:
	Cube(){}
	Cube(physical::ParticleManager &pm);
	~Cube();

	physical::ParticleGraph	getCubeGraph(){return m_cubeGraph;}
};

#endif //CUBE_H