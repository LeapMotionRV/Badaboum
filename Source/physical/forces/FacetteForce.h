#ifndef _IMAC3_FACETTEFORCE_HPP
#define _IMAC3_FACETTEFORCE_HPP


#include <glm/glm.hpp>

#include "Force.h"
#include "../LeapfrogSolver.h"
#include "../ParticleManager.h"
#include "../shapes/Facette.h"


namespace physical 
{
	class FacetteForce : public Force
	{
	public:
		FacetteForce(const Facette* pFacette, float elasticity, const LeapfrogSolver* solver):m_pFacette(pFacette), m_fElasticity(elasticity), m_Solver(solver), m_fDt(0.0001f){};
		
		bool isParticleInFacet(ParticleManager* pParticleManager, int particleIndex);

		void setDt(float dt);		
		void apply(ParticleManager* pm);
	private:
		//pointe sur le Facettee repoussant les particules
		const Facette* m_pFacette;
		//coef d'�lasticit� (1 -> �l�ments coll�s au sol / 2 -> �l�ments rebondissent sans perte d'�nergie
		float m_fElasticity;
		//servira � tester l'�tat suivant des particules
		const LeapfrogSolver* m_Solver;
		//argument � passer � la m�thode getNextState pour obtenir l'�tat suivant des particules
		float m_fDt;
	};
}

#endif // _IMAC3_FACETTE_FORCE_HPP
