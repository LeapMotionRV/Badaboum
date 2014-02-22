#ifndef MATHS_HPP
#define MATHS_HPP

#include <glm/glm.hpp>
#include <algorithm>

#include "shapes/Facette.h"
#include "shapes/Polygon.h"


namespace physical 
{

	//AB correspond à une arrête du polygon tandis que p1p2 correspond à p1 la position de la particule en t et p2 en t+dt
	//On considère M le point d'intersection entre P1P2 et AB, n la normale à AB en M
	inline bool intersect(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& A, const glm::vec3& B, glm::vec3* intersection, glm::vec3* normal) 
	{
		static const float epsilon = 0.001f; // Permet de tricher en allongeant la taille des coté

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
	inline bool intersectInfinitePlane(const Polygon* plane, const glm::vec3& p1, const glm::vec3& p2, glm::vec3* intersection, glm::vec3* normal, float size) 
	{
		// le radius permet que les particules se posent sur le terrain sans que ça soit au niveau de leur centre
		float radius = size*0.025f;
		//Direction of our particle
		glm::vec3 dir = p2-radius - p1-radius; // Vecteur p1p2

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
		float k = -(a*p1[0]-radius + b*p1[1]-radius + c*p1[2]-radius + d) / (a*dir[0] + b * dir[1] + c*dir[2]);
	
		// same result with : float k2 = - glm::dot(normale, p1 - A) / glm::dot(normale, dir);

		//find the intersection point	
		glm::vec3 I = p1-radius + k * dir;
		
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

	//NOT SURE THAT IT WORKS PERFECTLY, WORKS WITH A QUAD I THINK
	//intersection between facette and p1p2 vector (p1 position of particle in t and p2 position of particle in t+dt
	inline bool intersectFinishedPlane(const Polygon* polygon, const glm::vec3& p1, const glm::vec3& p2, glm::vec3* intersection, glm::vec3* normal) 
	{
		//get the min x of the polygon
		float minX = std::min(polygon->getPointArray()[2].x, std::min(polygon->getPointArray()[0].x, polygon->getPointArray()[1].x));
		//get the max x of the polygon
		float maxX = std::max(polygon->getPointArray()[2].x, std::max(polygon->getPointArray()[0].x, polygon->getPointArray()[1].x));
		//get the min y of the polygon 
		float minY = std::min(polygon->getPointArray()[2].y, std::min(polygon->getPointArray()[0].y, polygon->getPointArray()[1].y));
		//get the max y of the polygon
		float maxY = std::max(polygon->getPointArray()[2].y, std::max(polygon->getPointArray()[0].y, polygon->getPointArray()[1].y));
		//get the min y of the polygon 
		float minZ = std::min(polygon->getPointArray()[2].z, std::min(polygon->getPointArray()[0].z, polygon->getPointArray()[1].z));
		//get the min y of the polygon 
		float maxZ = std::max(polygon->getPointArray()[2].z, std::max(polygon->getPointArray()[0].z, polygon->getPointArray()[1].z));

		//if position of p2 is out the polygon, no intersection
		if(p2.x < minX || maxX < p2.x || p2.y < minY || maxY < p2.y || p2.z < minZ || maxZ < p2.z ){
			return false;
		}

		//Direction of our particle
		glm::vec3 dir = p2 - p1; // Vecteur p1p2

		//Compute the normal vector of the plane
		//Get the three points defining the plane
		glm::vec3 A = polygon->getPointArray()[0];
		glm::vec3 B = polygon->getPointArray()[1];
		glm::vec3 C = polygon->getPointArray()[2];
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

	//Facette is a triangle
	//see : http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
	inline bool intersectFacette(const Facette* pFacette, const glm::vec3& p1, const glm::vec3& p2, glm::vec3* intersection, glm::vec3* normal) 
	{
		static const float epsilon = 0.000001f;

		//three points of the triangle
		glm::vec3 t0 = *pFacette->getPointArray()[0];
		glm::vec3 t1 = *pFacette->getPointArray()[1];
		glm::vec3 t2 = *pFacette->getPointArray()[2];

		//Direction of our particle
		glm::vec3 dir = p2 - p1; // Vecteur p1p2

		//Find vectors for two edges sharing t1
		glm::vec3 edge1 = t1 - t0; 
		glm::vec3 edge2 = t2 - t0;  //Edge1, Edge2
		
		glm::vec3 normale = glm::cross(t1 - t0, t2 - t0);
		glm::vec3 P, Q, T;
		float det, inv_det, u, v;
		float k;
 
		//Begin calculating determinant - also used to calculate u parameter
		P = glm::cross(dir, edge2);
		//if determinant is near zero, ray lies in plane of triangle
		det = glm::dot(edge1, P);
		//NOT CULLING
		if(det > -epsilon && det < epsilon) return false;

		inv_det = 1.f / det;
 
		//calculate distance from t0 to ray origin
		T = p1 - t0;

		//Calculate u parameter and test bound
		u = glm::dot(T, P) * inv_det;

		//The intersection lies outside of the triangle
		if(u < 0.f || u > 1.f) return false;
 
		//Prepare to test v parameter
		Q = glm::cross(T, edge1);
 
		//Calculate V parameter and test bound
		v = glm::dot(dir, Q) * inv_det;
		//The intersection lies outside of the triangle
		if(v < 0.f || u + v  > 1.f) return false;
 
		k = glm::dot(edge2, Q) * inv_det;
 
		//I = p1 + k * dir; check if I is on p1p2
		if(k < 0.f || k > 1.f ) return false;

		if(k > epsilon) { //ray intersection
			
			glm::vec3 I = p1 + k * dir;

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

		return false;
			
		}
 
}

#endif // MATHS_HPP
