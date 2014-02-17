#ifndef LINK_H
#define LINK_H


#include "Shape.h"
#include "../ParticleManager.h"


namespace physical
{
	/**
		This shape describes a link between 2 particles.
	*/
	class Link : public Shape
	{
	public:
		Link(ParticleManager* pParticleManager, size_t idParticle1, size_t idParticle2);
		
		void applyInternalForces(ParticleManager* pParticleManager, float dt);
		void applyExternalForces(ParticleManager* pParticleManager, float dt);
		
		void draw(ParticleManager* pParticuleManager);

	private:
		//lenght of springs
		float m_L;
		//rigidity
		float m_K;
		//brake
		float m_V;//if you want the system to be more stable, decrease this variable
	};
}

#endif //LINK_H
