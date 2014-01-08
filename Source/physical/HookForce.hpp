#ifndef _IMAC3_HOOKFORCE_HPP
#define _IMAC3_HOOKFORCE_HPP


#include <glm/glm.hpp>

#include "Force.hpp"
#include "ParticuleManager.h"


namespace physical 
{
	
	//force d'oscillation entre deux particules
	class HookForce : public Force
	{
	public:
		HookForce(float fK, float fL):m_fK(fK), m_fL(fL){};
		~HookForce();
		void apply(ParticuleManager& pm);
	private:
		float m_fK;//raideur du ressort, va jouer sur la vitesse à laquelle la particule se déplace, plus c'est élevé, plus elle va vite
		float m_fL;//longueur à vide du ressort, va jouer sur l'amplitude de déplacement de la particule
	};
}

#endif // IMAC3_HOOKFORCE_HPP
