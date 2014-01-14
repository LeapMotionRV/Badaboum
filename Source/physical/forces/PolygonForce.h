#ifndef _IMAC3_POLYGONFORCE_HPP
#define _IMAC3_POLYGONFORCE_HPP


#include <glm/glm.hpp>

#include "Force.h"
#include "../LeapfrogSolver.h"
#include "../ParticleManager.h"
#include "../shapes/Polygon.h"


namespace physical 
{
	class PolygonForce : public Force
	{
	public:
		PolygonForce(){};
		PolygonForce(const Polygon* pPolygon, float elasticity, const LeapfrogSolver* solver):m_pPolygon(pPolygon), m_fElasticity(elasticity), m_Solver(solver), m_fDt(0.0001f){};
		
		void setDt(float dt);
				
		void apply(ParticleManager* pm);
	private:
		//pointe sur le polygone repoussant les particules
		const Polygon* m_pPolygon;
		//coef d'élasticité
		float m_fElasticity;
		//servira à tester l'état suivant des particules
		const LeapfrogSolver* m_Solver;
		//argument à passer à la méthode getNextState pour obtenir l'état suivant des particules
		float m_fDt;
	};
}

#endif // _IMAC3_POLYGONFORCE_HPP
