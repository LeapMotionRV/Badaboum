#ifndef MATHS_HPP
#define MATHS_HPP

#include <glm/glm.hpp>

namespace physical 
{

	//AB correspond à une arrête du polygon tandis que p1p2 correspond à p1 la position de la particule en t et p2 en t+dt
	//On considère M le point d'intersection entre P1P2 et AB, n la normale à AB en M
	inline bool intersectLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& A, const glm::vec3& B,
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

	//intersection between plane and p1p2 vector (p1 position of particle in t and p2 position of particle in t+dt
	inline bool intersectPlane(const Polygon* plane, const glm::vec3& p1, const glm::vec3& p2,
		glm::vec3* intersection, glm::vec3* normal) 
	{
		
		//Direction of our particle
		glm::vec3 dir = p2 - p1; // Vecteur p1p2

		//Compute the normal vector of the plane
		//Get the three points defining the plane
		glm::vec3 A = plane->getPointArray()[0];
		glm::vec3 B = plane->getPointArray()[1];
		glm::vec3 C = plane->getPointArray()[2];
		//Compute AB and AC vectors 
		glm::vec3 AB = B - A;
		glm::vec3 AC = C - A;
		//Compute the normal to the vectors with vector product
		glm::vec3 normale = glm::cross(AB,AC); 

		//case 1 : direction of particle is parallel to the plane (dot product is nul for orthogonal vectors)
		if(glm::dot(dir, normale) == 0)
		{
			return false;
		}

		//here we got the plane equation : ax+by+cz+d = 0 with normale(a,b,c), we missed d
		//A is on P so ax + by + cz + d = 0 so d = - (ax+...)
		float d = - glm::dot(A, normale);

		//The point of intersection I(x0,y0,z0) is equaled to p1 + k * dir 
		//so x0 = p1[0] + k * dir[0]
		// y0 = p1[1] + k * dir[1]
		// z0 = p1[2] + k * dir[2]
		// equation of the plane ax + by + cz + d = 0
		float a = normale[0];
		float b = normale[1];
		float c = normale[2];
		//I is on the plane so ax0 + by0 + cz0 + d = 0
		//we determined k thanks to this expression
		float k = -(a*p1[0] + b*p1[1] + c*p1[2] + d) / (a*dir[0] + b * dir[1] + c*dir[2]);
	
		// same result with : float k2 = - glm::dot(normale, p1 - A) / glm::dot(normale, dir);

		//find the intersection point	
		glm::vec3 I = p1 + k * dir;
		
		//if I isn't on p1p2
		if(k < 0.f || k > 1.f ){
			return false;
		}
		
		if(intersection) 
		{
			*intersection = I;
		}

		if(normal) 
		{
			*normal = glm::normalize(normale);
		}

		return true;
	}


}

#endif // MATHS_HPP
