#include <math.h>
#include <glm/glm.hpp>
#include <iostream>

#include "PolygonForce.h"
#include "maths.h"


namespace physical 
{
	void PolygonForce::setDt(float dt) {
		m_fDt = dt;
	}

	//AB correspond à une arrête du polygon tandis que p1p2 correspond à p1 la position de la particule en t et p2 en t+dt
	//On considère M le point d'intersection entre P1P2 et AB, n la normale à AB en M
	bool PolygonForce::intersect(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& A, const glm::vec3& B, glm::vec3* intersection, glm::vec3* normal) {
		return intersect(p1, p2, A, B, intersection, normal);
	}

	void PolygonForce::apply(ParticleManager& pm){
		glm::vec3 intersection;
		glm::vec3 normal;
		
		//boucle sur toutes les particules
		for (unsigned int particleIndex = 0; particleIndex < pm.getPositionArray().size(); ++particleIndex) 
		{
			ParticleState nextParticleState = m_Solver->getNextState(particleIndex, pm, m_fDt);
			
			//boucle sur les aretes du polygone, on ne va pas jusqu'au dernier point puisqu'il n'en possède pas de suivant
			for (unsigned int indexPointOfThePolygon = 0 ; indexPointOfThePolygon < m_Polygon->getPointArray().size(); indexPointOfThePolygon++) 
			{
				//si le polygon est interne
				if(m_Polygon->isInner())
				{
					//position de la particule en t, position en t+dt, points formant l'arête courante du polygon 
					if(intersect(pm.getPositionArray()[particleIndex], nextParticleState.m_position, m_Polygon->getPointArray()[indexPointOfThePolygon], m_Polygon->getPointArray()[(indexPointOfThePolygon+1)%m_Polygon->getPointArray().size()], &intersection, &normal ))
					{
						//il y a intersection alors on applique une force pour repousser la particule
						glm::vec3 forceRepulse;
						//elasticité = 1 => se colle à la paroi, e=2 => rebondit sans perte, e > 2 rebondit avec prise de vitesse
						//formule fournie dans l'énoncé
						forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm.getMassArray()[particleIndex]/m_fDt) * normal;
						//pm.resetForceOfParticle(particleIndex);
						pm.setForceOfParticle(forceRepulse, particleIndex);
					}
				//si le polygon est externe
				}
				else
				{
					if(intersect(pm.getPositionArray()[particleIndex], nextParticleState.m_position, m_Polygon->getPointArray()[(indexPointOfThePolygon+1)%m_Polygon->getPointArray().size()], m_Polygon->getPointArray()[indexPointOfThePolygon], &intersection, &normal ))
					{
						//il y a intersection alors on applique une force pour repousser la particule
						glm::vec3 forceRepulse;
						//elasticité = 1 => se colle à la paroi, e=2 => rebondit sans perte, e > 2 rebondit avec prise de vitesse
						//formule fournie dans l'énoncé
						forceRepulse = m_fElasticity * glm::dot(nextParticleState.m_speed, -normal) * (pm.getMassArray()[particleIndex]/m_fDt) * normal;
						//pm.resetForceOfParticle(particleIndex);
						pm.setForceOfParticle(forceRepulse, particleIndex);
					}
				}
				
			}

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
