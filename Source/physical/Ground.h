#ifndef _IMAC3_GROUND_HPP
#define _IMAC3_GROUND_HPP


#include <vector>

#include "forces/PolygonForce.h"
#include "shapes/Polygon.h"


namespace physical 
{
	class Ground 
	{
	public:
		Ground(){};

		void apply(ParticleManager* pm, float dt);
		void addPolygonAndForce(Polygon* pPolygon, PolygonForce* pPolygonForce);

		void draw();

		//getters
		std::vector<Polygon*>		getPolygonArray(){return m_polygonArray;}
		std::vector<PolygonForce*>	getPolygonForce(){return m_polygonForceArray;}

	private:
		std::vector<Polygon*>		m_polygonArray;
		std::vector<PolygonForce*>	m_polygonForceArray;
	};
}

#endif