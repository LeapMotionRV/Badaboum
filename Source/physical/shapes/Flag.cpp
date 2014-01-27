#include "Flag.h"
#include <iostream>
#include <cstdlib>

namespace physical{
	Flag::Flag(float mass, float width, float height, float depth, int gridWidth, int gridHeight, int gridDepth){
		m_pParticleManager = new ParticleManager();
		m_gridHeight = gridHeight;
		m_gridWidth= gridWidth;
		m_gridDepth = gridDepth;
		
		glm::vec3 origin(-0.5f * width, -0.5f * height, 0.5f * depth);
        //glm::vec3 scale(width / (gridWidth - 1), height / (gridHeight - 1), 1.f);
		//en partant du principe qu'on a en profondeur
		glm::vec3 scale(width / (gridWidth - 1), height / (gridHeight - 1), depth / (gridDepth - 1));

		float massOfParticle =  mass / (gridWidth * gridHeight * gridDepth);

		//creation de la face avant (occupe l'index 0 a gridHeight * gridWidth dans le tableau de particules)
		unsigned int currentIndex = 0;
		for(int j = 0; j < gridHeight; ++j) { //j corresponds to y 
            for(int i = 0; i < gridWidth; ++i) { // corresponds to x
				//ptet pose probleme, dans le td on a positionArray[i + j * gridWidth] = origin + glm::vec3(i, j, origin.z) * scale;
				m_pParticleManager->addParticle(origin + glm::vec3(i, j, 0.f) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)i/gridWidth,(float)j/gridHeight,(float)(1-i)/(float)(gridHeight)));
				currentIndex += 1;
			}
        }
		
		//creation de la face arriere
		for(int j = 0; j < gridHeight; ++j) { //j corresponds to y 
            for(int i = 0; i < gridWidth; ++i) { // corresponds to x
				m_pParticleManager->addParticle(origin + glm::vec3(i, j, - (gridDepth - 1)) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)i/gridWidth,(float)j/gridHeight,(float)(1-i)/(float)(gridHeight)));
				currentIndex+=1;
			}
        }
		
		//creation des particules manquantes (et seulement les manquantes, pas de doublons),
		//attention a utiliser gridWidth et gridHeight, car on multiplie par scale apres
		//face gauche (suivant yz)
		for(int j = 0; j < gridHeight; ++j) { //j corresponds to y 
            for(float k = 1; k < gridDepth - 1; ++k) { // corresponds to z
				m_pParticleManager->addParticle(origin + glm::vec3(0, j, - k) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)k/gridWidth,(float)j/gridHeight,(float)(1-k)/(float)(gridDepth)));
				currentIndex+=1;
			}
        }
		
		//face droite (suivant yz aussi),
		for(int j = 0; j < gridHeight; ++j) { //j corresponds to y 
            for(float k = 1; k < gridDepth - 1; ++k) { // corresponds to z
				m_pParticleManager->addParticle(origin + glm::vec3(gridWidth -1, j, - k) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)k/gridWidth,(float)j/gridHeight,(float)(1-k)/(float)(gridDepth)));
				currentIndex+=1;
			}
        }
		
		//face haute (suivant xz)
		for(int i = 1; i < gridWidth - 1; ++i) { //j corresponds to y 
            for(float k = 1; k < gridDepth - 1; ++k) { // corresponds to z
				m_pParticleManager->addParticle(origin + glm::vec3(i, gridHeight -1, - k) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)k/gridWidth,(float)i/gridHeight,(float)(1-k)/(float)(gridHeight)));
				currentIndex+=1;
			}
        }

		//face basse (suivant xz)
		for(int i = 1; i < gridWidth - 1; ++i) { //j corresponds to y 
            for(float k = 1; k < gridDepth - 1; ++k) { // corresponds to z
				m_pParticleManager->addParticle(origin + glm::vec3(i, 0.f, - k) * scale, glm::vec3(0.f), massOfParticle, glm::vec3(0.f), glm::vec3((float)k/gridWidth,(float)i/gridHeight,(float)(1-k)/(float)(gridHeight)));
				currentIndex+=1;
			}
        }

		// Les longueurs a vide sont calcules a partir de la position initiale des points sur le drapeau
        m_L0.x = scale.x;
        m_L0.y = scale.y;
        m_L1 = glm::length(m_L0);
        m_L2 = 2.f * m_L0;

        // Ces parametres sont a fixer pour avoir un systeme stable: HAVE FUN !
        m_K0 = 1.f;
        m_K1 = 1.f;
        m_K2 = 1.f;

        m_V0 = 0.1f;
        m_V1 = 0.1f;
        m_V2 = 0.1f;
	};

	
	Flag::~Flag()
	{
	}

	glm::vec3 Flag::hookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2) {
		static const float epsilon = 0.0001;
		glm::vec3 P1P2 = P2 - P1;
		float dP1P2 = glm::length(P1P2);
		glm::vec3 hookForce = K * (1-(L / std::max (dP1P2, epsilon))) * (P1P2);
		return hookForce;
	}

	glm::vec3 Flag::brakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2) {
		return V * ((v2 - v1)/dt);
	}

	void Flag::applyInternalForces(float dt){
		for(size_t k = 0; k < (m_gridWidth*m_gridHeight); k++){ //loop on every particle
            size_t i = k%m_gridWidth;
            size_t j = k/m_gridWidth;

            //check position of  the particle on the flag
            bool isBottom = (j==0 ? true : false);
            bool isTop = (j%(m_gridHeight-1)==0 ? true : false);
            bool isLeft = (i==0 ? true : false);
            bool isRight = (i%(m_gridWidth-1)==0 ? true : false);

            bool isOneBeforeBottom = (j==1 ? true : false);
            bool isOneBeforeTop = (j%(m_gridHeight-2)==0 ? true : false);
            bool isOneBeforeLeft = (i==1 ? true : false);
            bool isOneBeforeRight = (i%(m_gridWidth-2)==0 ? true : false);

            //points fixes
            if(isLeft)
                continue;
			else if(isRight)
                continue;
			else if(isBottom)
                continue;
			else if(isTop)
                continue;

            //topologie 0
			m_pParticleManager->addForceToParticle(hookForce(m_K0, m_L0.x, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-1]), k);
            m_pParticleManager->addForceToParticle(brakeForce(m_V0, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-1]), k);
            if(!isRight){
                m_pParticleManager->addForceToParticle(hookForce(m_K0, m_L0.x, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+1]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V0, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+1]), k);
            }
            if(!isTop){
                m_pParticleManager->addForceToParticle(hookForce(m_K0, m_L0.y, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V0, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth]), k);
            }
            if(!isBottom){
                m_pParticleManager->addForceToParticle(hookForce(m_K0, m_L0.y, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V0, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth]), k);
            }

            //topologie 1
            if(!isTop){
                m_pParticleManager->addForceToParticle(hookForce(m_K1, m_L1, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth-1]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V1, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth-1]), k);
            }
            if(!isTop && !isRight){
                m_pParticleManager->addForceToParticle(hookForce(m_K1, m_L1, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth+1]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V1, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-m_gridWidth+1]), k);
            }
            if(!isBottom){
                m_pParticleManager->addForceToParticle(hookForce(m_K1, m_L1, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth-1]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V1, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth-1]), k);
            }
            if(!isBottom && !isRight){
                m_pParticleManager->addForceToParticle(hookForce(m_K1, m_L1, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth+1]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V1, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+m_gridWidth+1]), k);
            }
            
            //topologie 2
            if(!isOneBeforeLeft){
                m_pParticleManager->addForceToParticle(hookForce(m_K2, m_L2.x, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-2]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V2, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-2]), k);
            }
            if(!isRight && !isOneBeforeRight) {
                m_pParticleManager->addForceToParticle(hookForce(m_K2, m_L2.x, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+2]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V2, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+2]), k);
            }
            if(!isTop && !isOneBeforeTop){
                m_pParticleManager->addForceToParticle(hookForce(m_K2, m_L2.y, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-2*m_gridWidth]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V2, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k-2*m_gridWidth]), k);
            }
            if(!isBottom && !isOneBeforeBottom){
                m_pParticleManager->addForceToParticle(hookForce(m_K2, m_L2.y, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+2*m_gridWidth]), k);
                m_pParticleManager->addForceToParticle(brakeForce(m_V2, dt, m_pParticleManager->getPositionArray()[k], m_pParticleManager->getPositionArray()[k+2*m_gridWidth]), k);
            }
        }
	}

	void Flag::update(float dt) {
		for(int j = 0; j < m_gridHeight; ++j) {
            for(int i = 0; i < m_gridWidth; ++i) {
                int k = i + j*m_gridWidth;
				//points fixes
                if(i == 0) 
                    continue;
                else if(i == m_gridWidth-1) 
                    continue;
                else if(j == 0) 
                    continue;
				else if(j == m_gridHeight-1) 
                    continue;
                glm::vec3 nextSpeed = m_pParticleManager->getSpeedArray()[k] + dt * (m_pParticleManager->getForceArray()[k] /m_pParticleManager->getMassArray()[k]);
                glm::vec3 nextPosition = m_pParticleManager->getPositionArray()[k] + dt * nextSpeed;
				m_pParticleManager->setSpeedOfParticle(nextSpeed, k);
				m_pParticleManager->setPositionOfParticle(nextPosition, k);
				m_pParticleManager->resetForceOfParticle(k);
            }
        }
        // Ne pas oublier de remettre les forces a 0 !
    }

	void Flag::draw(ParticleManager* pParticuleManager){
		
	}
}