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

		virtual void draw(ParticleManager* pParticuleManager) = 0;

		//getter
		ParticleGraph*	getGraph() const{return m_graph;}
		std::string		getName() const{return m_name;}

	protected:
		ParticleGraph*	m_graph;
		std::string		m_name;
	};
}

#endif //SHAPE_H