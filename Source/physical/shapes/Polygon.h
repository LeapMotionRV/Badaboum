#ifndef _IMAC3_POLYGON_HPP
#define _IMAC3_POLYGON_HPP


#include <vector>
#include <glm/glm.hpp>


namespace physical 
{
	class Polygon 
	{
	public:
		Polygon();
		Polygon(glm::vec3 positionTopLeft, glm::vec3 positionTopRight, glm::vec3 positionBottomLeft, glm::vec3 positionBottomRight, glm::vec3 color);
		
		void draw() const;
		//nécessaire de mettre const pour assurer qu'on va pas modifier l'objet sinon si on appelle sur un polygon const comme c'est le cas dans PolygonForce ça passe pas
		
		//getters
		std::vector<glm::vec3> getPointArray() const;
	private:
		glm::vec3 m_color;
		std::vector<glm::vec3> m_pointArray;
		float m_width;
		float m_height;
	};
}

#endif // IMAC3_POLYGON_HPP
