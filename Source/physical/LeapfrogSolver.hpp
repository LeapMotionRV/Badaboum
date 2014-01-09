#ifndef _IMAC3_LEAPFROGSOLVER_HPP
#define _IMAC3_LEAPFROGSOLVER_HPP


//c'est ParticleManager qui contient la structure ParticleState permettant d'accéder à l'état suivant de la particule
#include "ParticuleManager.h" 


namespace physical {

	class LeapfrogSolver {
	public:
		void solve(ParticuleManager& pm, float dt);
		ParticuleState getNextState(uint32_t particleIdx, ParticuleManager& pm, float dt) const;
	};

}

#endif