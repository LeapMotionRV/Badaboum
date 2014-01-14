#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


//c'est ParticleManager qui contient la structure ParticleState permettant d'accéder à l'état suivant de la particule
#include "ParticleManager.h"
#include "Polygon.h"
#include "LeapfrogSolver.h"
#include "ConstantForce.h"
#include "PolygonForce.h"
#include "HookForce.h"
#include "../shape/Cube.h"


namespace physical 
{
	class Model 
	{
	public:
		Model(unsigned int countParticles = 0);
		void startSimulation(float dt);

		ParticleManager getParticuleManager(){return m_particleManager;}
		Polygon getGround(){return m_ground;}
		Cube getCube(){return m_cube;}
		LeapfrogSolver getLeapfrogSolver(){return m_leapfrogSolver;}
		ConstantForce getGravity(){return m_gravity;}
		PolygonForce getPolygonForce(){return m_polygonForce;}
		HookForce getHookForce(){return m_hookForce;}

	private:
		//data on the scene
		ParticleManager		m_particleManager;
		Polygon				m_ground;
		//forces
		LeapfrogSolver		m_leapfrogSolver;
		ConstantForce		m_gravity;
		PolygonForce		m_polygonForce;
		HookForce			m_hookForce;
		Cube				m_cube;
	};
}

#endif