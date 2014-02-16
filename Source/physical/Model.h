#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


#include "ParticleManager.h"
#include "LeapfrogSolver.h"
#include "forces/ConstantForce.h"
#include "forces/HookForce.h"
#include "forces/BrakeForce.h"
#include "forces/FacetteForce.h"
#include "Ground.h"
#include "shapes/Line.h"
#include "shapes/Facette.h"
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
		void addRandomParticle();//called when press "P"
		void addRandomLine();//called when press "L"

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
		Facette*						getFacette(){return m_pFacette;}

	private:
		LeapfrogSolver*					m_pLeapfrogSolver;
		//physical objects
		ParticleManager*				m_pParticleManager;
		std::vector<Shape*>				m_pShapeArray;
		//forces
		ConstantForce*					m_pGravity;
		ConstantForce*					m_pWind;
		HookForce*						m_pHookForce;			//unused
		BrakeForce*						m_pBrakeForce;			//unused
		std::vector<GraphHookForce*>	m_pGraphHookForceArray;	//unused
		std::vector<GraphBrakeForce*>	m_pGraphBrakeForceArray;//unused
		//getters - physical object + forces
		Ground*							m_pGround;
		Facette*						m_pFacette;
		FacetteForce*					m_pFacetteForce;
	};
}

#endif