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
	};
}

#endif //CUBE_H