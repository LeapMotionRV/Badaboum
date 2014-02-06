#include <math.h>
#include <iostream>

#include "Facette.h"
#include "../../util/LeapUtilGL.h"


namespace physical 
{
	Facette::Facette(const glm::vec3* firstPoint, const glm::vec3* secondPoint, const glm::vec3* thirdPoint, glm::vec3 color) {
		m_color = color;
		m_pointArray.push_back(firstPoint);
		m_pointArray.push_back(secondPoint);
		m_pointArray.push_back(thirdPoint);
	}

	/*void Facette::draw() const {
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.x, m_color.y, m_color.z);
		LeapUtilGL::drawFacet(LeapUtilGL::eStyle::kStyle_Solid, *m_pointArray[0], *m_pointArray[1], *m_pointArray[2]);
	}*/
}