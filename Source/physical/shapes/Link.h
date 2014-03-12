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
		
		//forces
		void applyInternalForces(ParticleManager* pParticleManager, float dt);
		void applyExternalForces(ParticleManager* pParticleManager, float dt);

		//when the lenght > (2*m_maxLenghtToCreateLink)
		bool isValid(ParticleManager* pParticleManager) const;
		
		//draw
		void draw(ParticleManager* pParticuleManager);

		/**
		* Getters
		*/
		float getSpringLenght(){return m_L;}
		
		static float getRigidity(){return s_K;}
		static float getBrake(){return s_V;}

		/**
		* Setters
		*/
		static void setRigidity(float rigidity){s_K = rigidity;}
		static void setBrake(float brake){s_V = brake;}

	private:
		//lenght of springs
		float m_L;
		
		//rigidity
		static float s_K;
		//brake
		static float s_V;//if you want the system to be more stable, decrease this variable
	};
}

#endif //LINK_H
