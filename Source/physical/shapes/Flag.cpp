#include "Flag.h"
#include <iostream>
#include <cstdlib>

namespace physical{
	Flag::Flag(float mass, float width, float height, int gridWidth, int gridHeight){
		m_gridHeight = gridHeight;
		m_gridHeight = gridWidth;
		m_flagParticles = ParticleManager();
		glm::vec3 origin(-0.5f * width, -0.5f * height, 0.f);
        glm::vec3 scale(width / (gridWidth - 1), height / (gridHeight - 1), 1.f);

		float massOfParticle =  mass / (gridWidth * gridHeight);
		for(int j = 0; j < gridHeight; ++j) { //j corresponds to y 
            for(int i = 0; i < gridWidth; ++i) { // corresponds to x
				//ptet pose problème, dans le td on a positionArray[i + j * gridWidth] = origin + glm::vec3(i, j, origin.z) * scale;
				m_flagParticles.addParticle(origin + glm::vec3(i, j, origin.z) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)i/gridWidth,(float)j/gridHeight,(float)(1-i)/(float)(gridHeight)));
            }
        }

		// Les longueurs à vide sont calculés à partir de la position initiale des points sur le drapeau
        m_L0.x = scale.x;
        m_L0.y = scale.y;
        m_L1 = glm::length(m_L0);
        m_L2 = 2.f * m_L0;

        // Ces paramètres sont à fixer pour avoir un système stable: HAVE FUN !
        m_K0 = 1.f;
        m_K1 = 1.f;
        m_K2 = 1.f;

        m_V0 = 0.1f;
        m_V1 = 0.1f;
        m_V2 = 0.1f;
	};

	// Calcule une force de type ressort de Hook entre deux particules de positions P1 et P2
	// K est la rÃ©sistance du ressort et L sa longueur Ã  vide
	glm::vec3 hookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2) {
		static const float epsilon = 0.0001;
		glm::vec3 P1P2 = P2 - P1;
		float dP1P2 = glm::length(P1P2);
		return K * (1-(L / std::max (dP1P2, epsilon))) * (P1P2);
	}

	// Calcule une force de type frein cinÃ©tique entre deux particules de vÃ©locitÃ©s v1 et v2
	// V est le paramÃ¨tre du frein et dt le pas temporel
	glm::vec3 brakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2) {
		return V * ((v2 - v1)/dt);
	}

	/*void Flag::applyInternalForces(float dt){
		for(size_t k = 0; k < m_flagParticles.getPositionArray().size(); k++){ //loop on every particle
            size_t i = k%m_gridWidth;
            size_t j = k/m_gridWidth;

            //check position of  the particle on the flag
            bool isTop = (j==0 ? true : false);
            bool isBottom = (j%(m_gridHeight-1)==0 ? true : false);
            bool isLeft = (i==0 ? true : false);
            bool isRight = (i%(m_gridWidth-1)==0 ? true : false);

            bool isOneBeforeTop = (j==1 ? true : false);
            bool isOneBeforeBottom = (j%(m_gridHeight-2)==0 ? true : false);
            bool isOneBeforeLeft = (i==1 ? true : false);
            bool isOneBeforeRight = (i%(m_gridWidth-2)==0 ? true : false);

            //point fixe
            if(isLeft)
                continue;

            //topologie 0
            m_flagParticles.getForceArray()[k] += hookForce(m_K0, m_L0.x, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-1]);
            m_flagParticles.getForceArray()[k] += brakeForce(m_V0, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-1]);
            if(!isRight){
                m_flagParticles.getForceArray()[k] += hookForce(m_K0, m_L0.x, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+1]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V0, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+1]);
            }
            if(!isTop){
                m_flagParticles.getForceArray()[k] += hookForce(m_K0, m_L0.y, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V0, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth]);
            }
            if(!isBottom){
                m_flagParticles.getForceArray()[k] += hookForce(m_K0, m_L0.y, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V0, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth]);
            }

            //topologie 1
            if(!isTop){
                m_flagParticles.getForceArray()[k] += hookForce(m_K1, m_L1, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth-1]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V1, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth-1]);
            }
            if(!isTop && !isRight){
                m_flagParticles.getForceArray()[k] += hookForce(m_K1, m_L1, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth+1]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V1, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-m_gridWidth+1]);
            }
            if(!isBottom){
                m_flagParticles.getForceArray()[k] += hookForce(m_K1, m_L1, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth-1]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V1, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth-1]);
            }
            if(!isBottom && !isRight){
                m_flagParticles.getForceArray()[k] += hookForce(m_K1, m_L1, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth+1]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V1, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+m_gridWidth+1]);
            }
            
            //topologie 2
            if(!isOneBeforeLeft){
                m_flagParticles.getForceArray()[k] += hookForce(m_K2, m_L2.x, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-2]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V2, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-2]);
            }
            if(!isRight && !isOneBeforeRight) {
                m_flagParticles.getForceArray()[k] += hookForce(m_K2, m_L2.x, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+2]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V2, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+2]);
            }
            if(!isTop && !isOneBeforeTop){
                m_flagParticles.getForceArray()[k] += hookForce(m_K2, m_L2.y, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-2*m_gridWidth]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V2, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k-2*m_gridWidth]);
            }
            if(!isBottom && !isOneBeforeBottom){
                m_flagParticles.getForceArray()[k] += hookForce(m_K2, m_L2.y, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+2*m_gridWidth]);
                m_flagParticles.getForceArray()[k] += brakeForce(m_V2, dt, m_flagParticles.getPositionArray()[k], m_flagParticles.getPositionArray()[k+2*m_gridWidth]);
            }
        }
	} */

	void Flag::update(float dt) {
        for(int j = 0; j < m_gridHeight; ++j) {
            for(int i = 0; i < m_gridWidth; ++i) {
                int k = i + j*m_gridWidth;
                if(k%m_gridWidth == 0) //point fixe
                    continue;
                glm::vec3 nextSpeed = m_flagParticles.getSpeedArray()[k] + dt * (m_flagParticles.getForceArray()[k] /m_flagParticles.getMassArray()[k]);
                glm::vec3 nextPosition = m_flagParticles.getPositionArray()[k] + dt * nextSpeed;
                m_flagParticles.getSpeedArray()[k] = nextSpeed;
                m_flagParticles.getPositionArray()[k] = nextPosition;
                m_flagParticles.getForceArray()[k] = glm::vec3(0,0,0);
            }
        }
        // Ne pas oublier de remettre les forces à 0 !
    }

	ParticleManager Flag::getFlagParticles(){
		return m_flagParticles;
	}

	Flag::~Flag()
	{
	}
}