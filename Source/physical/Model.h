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
		void initGround(const size_t size);
		void reset();

		/**
		* Apply forces and solved them with the leapfrogSolver
		*/
		void startSimulation(float dt);

		/**
		* Manage data of the scene
		*/
		void addRandomParticles(unsigned int count);//called when press "P"
		void addRandomLine();//called when press "L"
		void addParticleWhereLeapIs(glm::vec3 pos); //with leap motion

		/**
		* Getters
		*/
		LeapfrogSolver*					getLeapfrogSolver(){return m_pLeapfrogSolver;}
		ParticleManager*				getParticuleManager(){return m_pParticleManager;}
		LinkManager*					getLinkManager(){return m_pLinkManager;}
		std::vector<ConstantForce*>		getConstantForceArray(){return m_constantForceArray;}
		Ground*							getGround(){return m_pGround;}
		unsigned int					getNbMaxParticle(){return m_nbMaxParticle;}
		float							getNbHumanInitial(){return m_nbHumanInitial;}
		float							getNbHumanLeft(){return m_nbHumanLeft;}

		bool isPlayerWin() const;
		bool isPlayerLoose() const;

		/**
		* Setters
		*/
		void setGravity(float gravity){ m_constantForceArray[0]->setForce(glm::vec3(0.f, gravity, 0.f));}
		void isPlayerWin(bool flag) {m_bIsPlayerWin = flag;}
		void isPlayerLoose(bool flag) {m_bIsPlayerLoose = flag;}

		void setHumanAlive(unsigned int nbParticles, int time){
			if(m_previousParticleNb!=nbParticles){
				++m_previousParticleNb;
				m_nbHumanLeft -= 100000000 + time;
			}
			else
				m_nbHumanLeft -= time;

			if(m_nbHumanLeft < 0) m_nbHumanLeft = 0;
		}

		//suppress warning
		Model & operator=( const Model & ) {}

	private:
		bool							m_bIsPlayerLoose;
		bool							m_bIsPlayerWin;
		LeapfrogSolver*					m_pLeapfrogSolver;
		
		//physical objects
		ParticleManager*				m_pParticleManager;
		LinkManager*					m_pLinkManager;
		
		//forces
		std::vector<ConstantForce*>		m_constantForceArray; //contains gravity, possible wind, etc...
		
		//getters - physical object + forces
		Ground*							m_pGround;
		const unsigned int				m_nbMaxParticle;

		//human number controle
		const float		m_nbHumanInitial;
		float			m_nbHumanLeft;
		unsigned int	m_previousParticleNb;
	};
}

#endif