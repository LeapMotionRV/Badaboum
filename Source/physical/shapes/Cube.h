#ifndef CUBE_H
#define CUBE_H


#include "Shape.h"
#include "../ParticleManager.h"


namespace physical
{
	class Cube : public Shape
	{
	public:
		Cube(ParticleManager* pParticuleManager);
	};
}

#endif //CUBE_H