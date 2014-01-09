#ifndef _IMAC3_POLYGONFORCE_HPP
#define _IMAC3_POLYGONFORCE_HPP

#include <glm/glm.hpp>

#include "Force.h"
#include "Polygon.h"
#include "LeapfrogSolver.h"
#include "ParticleManager.h"


namespace physical 
{
	class PolygonForce : public Force
	{
	public:
		PolygonForce(){};
		PolygonForce(const Polygon* polygon, float elasticity, const LeapfrogSolver* solver):m_Polygon(polygon), m_fElasticity(elasticity), m_Solver(solver), m_fDt(0.0001f){};
		void setDt(float dt);
		bool intersect(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& A, const glm::vec3& B, glm::vec3* intersection, glm::vec3* normal);
		void apply(ParticleManager& pm);
		void applyForce(ParticleManager& pm);
	private:
		//pointe sur le polygone repoussant les particules
		const Polygon* m_Polygon;
		//coef d'élasticité
		float m_fElasticity;
		//servira à tester l'état suivant des particules
		const LeapfrogSolver* m_Solver;
		//argument à passer à la méthode getNextState pour obtenir l'état suivant des particules
		float m_fDt;
	};
}

#endif // _IMAC3_POLYGONFORCE_HPP
