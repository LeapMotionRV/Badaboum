#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


#include "ParticleManager.h"
#include "LeapfrogSolver.h"
#include "forces/ConstantForce.h"
#include "forces/PolygonForce.h"
#include "forces/HookForce.h"
#include "forces/BrakeForce.h"
#include "shapes/Polygon.h"
#include "shapes/Cube.h"
#include "forces/GraphHookForce.h"
#include "forces/GraphBrakeForce.h"


namespace physical 
{
	class Model 
	{
	public:
		Model(unsigned int countParticles = 0);

		//apply forces and solved them with the leapfrogSolver
		void startSimulation(float dt);

		//getters - physical objects
		ParticleManager*	getParticuleManager(){return m_pParticleManager;}
		Polygon*			getGround(){return m_pGround;}
		Cube*				getCube(){return m_pCube;}
		//getters - forces
		LeapfrogSolver*		getLeapfrogSolver(){return m_pLeapfrogSolver;}
		ConstantForce*		getGravity(){return m_pGravity;}
		PolygonForce*		getPolygonForce(){return m_pPolygonForce;}
		HookForce*			getHookForce(){return m_pHookForce;}
		BrakeForce*			getBrakeForce(){return m_pBrakeForce;}
		GraphHookForce*		getGraphHookForce(){return m_pGraphHookForce;}
		GraphBrakeForce*	getGraphBrakeForce(){return m_pGraphBrakeForce;}

	private:
		//physical objects
		ParticleManager*	m_pParticleManager;
		Polygon*			m_pGround;
		Cube*				m_pCube;
		//forces
		LeapfrogSolver*		m_pLeapfrogSolver;
		ConstantForce*		m_pGravity;
		PolygonForce*		m_pPolygonForce;
		HookForce*			m_pHookForce;
		BrakeForce*			m_pBrakeForce;
		GraphHookForce*		m_pGraphHookForce;
		GraphBrakeForce*	m_pGraphBrakeForce;
	};
}

#endif