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
		Polygon(glm::vec3 color, glm::vec3 center, float width, float height, bool isInner = false);
		void draw() const;
		//nécessaire de mettre const pour assurer qu'on va pas modifier l'objet sinon si on appelle sur un polygon const comme c'est le cas dans PolygonForce ça passe pas
		bool isInner() const;
		std::vector<glm::vec3> getPointArray() const;
	private:
		glm::vec3 m_color;
		bool m_bIsInner;
		std::vector<glm::vec3> m_pointArray;
		float m_width;
		float m_height;
	};
}

#endif // IMAC3_POLYGON_HPP
