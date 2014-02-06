#ifndef _IMAC3_FACETTE_HPP
#define _IMAC3_FACETTE_HPP

#include <vector>
#include <glm/glm.hpp>


namespace physical 
{
	class Facette 
	{
	public:
		//construct
		Facette(const glm::vec3* firstPoint, const glm::vec3* secondPoint, const glm::vec3* thirdPoint, glm::vec3 color);
		//draw
		//void draw() const;
		//getters
		std::vector<const glm::vec3*> getPointArray() const {return m_pointArray;}
	
	private:
		glm::vec3 m_color;
		std::vector<const glm::vec3*> m_pointArray;
	};
}

#endif // IMAC3_FACETTE_HPP
