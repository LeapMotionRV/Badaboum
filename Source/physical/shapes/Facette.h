#ifndef _IMAC3_FACETTE_HPP
#define _IMAC3_FACETTE_HPP

#include <vector>
#include <glm/glm.hpp>


namespace physical 
{
	class Facette 
	{
	public:
		Facette();
		Facette(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, glm::vec3 color);
		
		void draw() const;
		
		//getters
		std::vector<glm::vec3> getPointArray() const;
	
	private:
		glm::vec3 m_color;
		std::vector<glm::vec3> m_pointArray;
	};
}

#endif // IMAC3_FACETTE_HPP
