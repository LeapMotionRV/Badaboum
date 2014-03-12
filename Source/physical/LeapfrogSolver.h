#ifndef _IMAC3_LEAPFROGSOLVER_HPP
#define _IMAC3_LEAPFROGSOLVER_HPP

//c'est ParticleManager qui contient la structure ParticleState permettant d'accéder à l'état suivant de la particule
#include "ParticleManager.h" 

namespace physical {

	class LeapfrogSolver {
	public:
		void solve(ParticleManager* pm, float dt);
		ParticleState getNextState(size_t particleIdx, ParticleManager* pm, float dt) const;
	};

}

#endif