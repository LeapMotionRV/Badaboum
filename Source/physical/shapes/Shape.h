#ifndef SHAPE_H
#define SHAPE_H


#include "../ParticleManager.h"


namespace physical
{
	/**
		Represent a shape, with an empty list of links between particles.
	*/
	class Shape
	{
	public:
		Shape();
		~Shape();

		//getter
		const ParticleGraph* getGraph(){return m_graph;}

	protected:
		ParticleGraph* m_graph;
	};
}

#endif //SHAPE_H