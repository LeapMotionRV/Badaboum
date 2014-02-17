#ifndef _IMAC3_MODEL_HPP
#define _IMAC3_MODEL_HPP


#include "ParticleManager.h"
#include "LinkManager.h"
#include "LeapfrogSolver.h"
#include "forces/ConstantForce.h"
#include "Ground.h"


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
		void initParticleGround(float size);
		void initGround(float size);

		//getters
		LeapfrogSolver*					getLeapfrogSolver(){return m_pLeapfrogSolver;}
		ParticleManager*				getParticuleManager(){return m_pParticleManager;}
		LinkManager*					getLinkManager(){return m_pLinkManager;}
		std::vector<Shape*>				getShapeArray(){return m_pShapeArray;}
		ConstantForce*					getGravity(){return m_pGravity;}
		ConstantForce*					getWind(){return m_pWind;}
		Ground*							getGround(){return m_pGround;}

	private:
		LeapfrogSolver*					m_pLeapfrogSolver;
		//physical objects
		ParticleManager*				m_pParticleManager;
		LinkManager*					m_pLinkManager;
		std::vector<Shape*>				m_pShapeArray;
		//forces
		ConstantForce*					m_pGravity;
		ConstantForce*					m_pWind;
		//getters - physical object + forces
		Ground*							m_pGround;
	};
}

#endif