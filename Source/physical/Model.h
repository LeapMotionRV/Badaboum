#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


#include "ParticleManager.h"
#include "LeapfrogSolver.h"
#include "forces/ConstantForce.h"
#include "forces/HookForce.h"
#include "forces/BrakeForce.h"
#include "Ground.h"
#include "shapes/Cube.h"
#include "shapes/Line.h"
#include "shapes/Flag.h"
#include "forces/GraphHookForce.h"
#include "forces/GraphBrakeForce.h"


namespace physical 
{
	class Model 
	{
	public:
		Model(unsigned int countParticles = 0);
		~Model();

		//apply forces and solved them with the leapfrogSolver
		void startSimulation(float dt);

		//create data for the scene
		//called when press "P"
		void addRandomParticle();
		//called when press "C"
		void addRandomCube();
		//called when press "L"
		void addRandomLine();
		void addHookAndBrakeForceToShape(Shape* pShape, float raideur, float longueur, float fV);

		//getters
		LeapfrogSolver*					getLeapfrogSolver(){return m_pLeapfrogSolver;}
		ParticleManager*				getParticuleManager(){return m_pParticleManager;}
		std::vector<Shape*>				getShapeArray(){return m_pShapeArray;}
		ConstantForce*					getGravity(){return m_pGravity;}
		ConstantForce*					getWind(){return m_pWind;}
		HookForce*						getHookForce(){return m_pHookForce;}
		BrakeForce*						getBrakeForce(){return m_pBrakeForce;}
		std::vector<GraphHookForce*>	getGraphHookForceArray(){return m_pGraphHookForceArray;}
		std::vector<GraphBrakeForce*>	getGraphBrakeForceArray(){return m_pGraphBrakeForceArray;}
		Ground*							getGround(){return m_pGround;}
		Flag*							getFlag(){return dynamic_cast<physical::Flag*>(m_pShapeArray[0]);}

	private:
		LeapfrogSolver*					m_pLeapfrogSolver;
		//physical objects
		ParticleManager*				m_pParticleManager;
		std::vector<Shape*>				m_pShapeArray;
		//forces
		ConstantForce*					m_pGravity;
		ConstantForce*					m_pWind;
		HookForce*						m_pHookForce;
		BrakeForce*						m_pBrakeForce;
		std::vector<GraphHookForce*>	m_pGraphHookForceArray;
		std::vector<GraphBrakeForce*>	m_pGraphBrakeForceArray;
		//getters - physical object + forces
		Ground*							m_pGround;
	};
}

#endif