#include "Ground.h"


namespace physical 
{
	void Ground::addPolygonAndForce(Polygon* pPolygon, PolygonForce* pPolygonForce) {
		m_polygonArray.push_back(pPolygon);
		m_polygonForceArray.push_back(pPolygonForce);
	}

	void Ground::apply(ParticleManager* pm, float dt){
		for(unsigned int i = 0; i <= m_polygonForceArray.size()-1; ++i){
			m_polygonForceArray[i]->setDt(dt);
			m_polygonForceArray[i]->apply(pm);
		}
	}

	void Ground::draw(){
		for(unsigned int i = 0; i <= m_polygonForceArray.size()-1; ++i){
			m_polygonArray[i]->draw();
		}
	}
}