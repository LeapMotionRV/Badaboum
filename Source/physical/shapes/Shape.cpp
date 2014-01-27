#include "Shape.h"

namespace physical
{

	Shape::Shape()
	{
		m_graph = new ParticleGraph();
		m_name = "Shape";
	}

	Shape::~Shape()
	{
	}
}