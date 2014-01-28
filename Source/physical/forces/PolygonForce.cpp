#include <math.h>
#include <glm/glm.hpp>
#include <iostream>
#include "PolygonForce.h"
#include "../maths.h"


namespace physical 
{
	void PolygonForce::setDt(float dt) {
		m_fDt = dt;
	}

	void PolygonForce::apply(ParticleManager* pm){
		glm::vec3 intersection;
		glm::vec3 normal;
		
		//boucle sur toutes les particules
		for (unsigned int particleIndex = 0; particleIndex < pm->getPositionArray().size(); ++particleIndex) 
		{
			ParticleState nextParticleState = m_Solver->getNextState(particleIndex, pm, m_fDt);
			
			/*INTERSECTION BETWEEN VECTOR AND PLANE*/
			if(intersectPlane(m_pPolygon, pm->getPositionArray()[particleIndex], nextParticleState.m_position, &intersection, &normal ))
 			{
				//il y a intersection alors on applique une force pour repousser la particule
				glm::vec3 forceRepulse;
				//formule fournie dans l'énoncé
				forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm->getMassArray()[particleIndex]/m_fDt) * normal;
				//pm.resetForceOfParticle(particleIndex);
				pm->setForceOfParticle(forceRepulse, particleIndex);
			}

			/*INTERSECTION BETWEEN TWO VECTORS*/
			//boucle sur les aretes du polygone, on ne va pas jusqu'au dernier point puisqu'il n'en possède pas de suivant
		/*	for (unsigned int indexPointOfThePolygon = 0 ; indexPointOfThePolygon < m_pPolygon->getPointArray().size(); indexPointOfThePolygon++) 
			{
				//si le polygon est interne
				if(m_pPolygon->isInner())
				{
					//position de la particule en t, position en t+dt, points formant l'arête courante du polygon 
					if(intersect(pm->getPositionArray()[particleIndex], nextParticleState.m_position, m_pPolygon->getPointArray()[indexPointOfThePolygon], m_pPolygon->getPointArray()[(indexPointOfThePolygon+1)%m_pPolygon->getPointArray().size()], &intersection, &normal ))
					{
						//il y a intersection alors on applique une force pour repousser la particule
						glm::vec3 forceRepulse;
						//elasticité = 1 => se colle à la paroi, e=2 => rebondit sans perte, e > 2 rebondit avec prise de vitesse
						//formule fournie dans l'énoncé
						forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm->getMassArray()[particleIndex]/m_fDt) * normal;
						//pm.resetForceOfParticle(particleIndex);
						pm->setForceOfParticle(forceRepulse, particleIndex);
					}
				//si le polygon est externe
				}
				else
				{
					if(intersect(pm->getPositionArray()[particleIndex], nextParticleState.m_position, m_pPolygon->getPointArray()[(indexPointOfThePolygon+1)%m_pPolygon->getPointArray().size()], m_pPolygon->getPointArray()[indexPointOfThePolygon], &intersection, &normal ))
					{
						//il y a intersection alors on applique une force pour repousser la particule
						glm::vec3 forceRepulse;
						//elasticité = 1 => se colle à la paroi, e=2 => rebondit sans perte, e > 2 rebondit avec prise de vitesse
						//formule fournie dans l'énoncé
						forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm->getMassArray()[particleIndex]/m_fDt) * normal;
						//pm.resetForceOfParticle(particleIndex);
						pm->setForceOfParticle(forceRepulse, particleIndex);
					}
				}
				
			}*/

			// //il faut aussi tester entre le dernier et le premier point du polygone
			// if(intersect(pm.getPositionArray()[particleIndex], nextParticleState.m_position, m_Polygon->getPointArray()[m_Polygon->getPointArray().size() - 1], m_Polygon->getPointArray()[0], &intersection, &normal )){
			// 	//il y a intersection alors on applique une force pour repousser la particule
			// 	glm::vec2 forceRepulse;
			// 	//elasticité = 1 => se colle à la paroi, e=2 => rebondit sans perte, e > 2 rebondit avec prise de vitesse
			// 	//formule fournie dans l'énoncé
			// 	forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm.getMassArray()[particleIndex]/m_fDt) * normal;
			// 	//pm.resetForceOfParticle(particleIndex);
			// 	pm.setForceOfParticle(forceRepulse, particleIndex);
			// }
		}
	}
}
