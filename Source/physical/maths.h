#ifndef MATHS_HPP
#define MATHS_HPP

#include <glm/glm.hpp>

namespace physical 
{

	//AB correspond à une arrête du polygon tandis que p1p2 correspond à p1 la position de la particule en t et p2 en t+dt
	//On considère M le point d'intersection entre P1P2 et AB, n la normale à AB en M
	inline bool intersect(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& A, const glm::vec3& B,
		glm::vec3* intersection, glm::vec3* normal) 
	{
		static const float epsilon = 0.001; // Permet de tricher en allongeant la taille des coté

		glm::vec3 dir = p2 - p1; // Vecteur p1p2
		glm::vec3 AB = B - A; // Vecteur AB
		//glm::vec2 N = glm::vec3(-AB.y, AB.x); // Vecteur normal non unitaire
		glm::vec3 N = glm::cross(A, B);

		// Si le vecteur p1p2 et le vecteur N on la meme direction, il n'y a pas d'intersection
		if(glm::dot(dir, N) >= 0) {
			return false;
		}

		// Calcul du parametre t tel que I = p1 + t x p1p2
		float t = -glm::dot(N, p1 - A) / glm::dot(N, dir);

		// Si t n'est pas dans [0,1], le point d'intersection n'est pas dans le segment [p1,p2]
		if(t < 0.f || t > 1) {
			return false;
		}

		glm::vec3 I = p1 + t * dir; // Point d'intersection

		float dot = glm::dot(I - A, AB); // Produit scalaire entre le vecteur AI et le vecteur AB
		if(dot < -epsilon || dot > glm::dot(AB, AB) + epsilon) {
			return false;
		}

		if(intersection) {
			*intersection = I;
		}

		if(normal) {
			*normal = glm::normalize(N);
		}

		return true;
	}

}

#endif // MATHS_HPP
