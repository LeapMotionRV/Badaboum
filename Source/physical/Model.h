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
		void initGround(float size);

		//apply forces and solved them with the leapfrogSolver
		void startSimulation(float dt);

		//create data for the scene
		void addRandomParticle();//called when press "P"
		void addRandomLine();//called when press "L"
		void addParticleWhereLeapIs(glm::vec3 pos); //with leap motion

		//getters
		LeapfrogSolver*					getLeapfrogSolver(){return m_pLeapfrogSolver;}
		ParticleManager*				getParticuleManager(){return m_pParticleManager;}
		LinkManager*					getLinkManager(){return m_pLinkManager;}
		std::vector<ConstantForce*>		getConstantForceArray(){return m_constantForceArray;}
		Ground*							getGround(){return m_pGround;}
		unsigned int					getNbMaxParticle(){return m_nbMaxParticle;}

		//setters
		void							setGravity(float gravity){ m_gravity->setForce(glm::vec3(0.f, gravity, 0.f));}

	private:
		LeapfrogSolver*					m_pLeapfrogSolver;
		//physical objects
		ParticleManager*				m_pParticleManager;
		LinkManager*					m_pLinkManager;
		//forces
		std::vector<ConstantForce*>		m_constantForceArray; //contains gravity, possible wind, etc...
		//getters - physical object + forces
		Ground*							m_pGround;
		const unsigned int				m_nbMaxParticle;
		ConstantForce*					m_gravity;	
	};
}

#endif