#include <math.h>
#include <iostream>

#include "Facette.h"
#include "../../util/LeapUtilGL.h"


namespace physical 
{
	Facette::Facette() {
		m_color = glm::vec3(0.f, 0.f, 1.f);
	}

	Facette::Facette(glm::vec3* firstPoint, glm::vec3* secondPoint, glm::vec3* thirdPoint, glm::vec3 color) {
		m_color = color;
		m_pointArray.push_back(firstPoint);
		m_pointArray.push_back(secondPoint);
		m_pointArray.push_back(thirdPoint);
	}

	std::vector<glm::vec3*> Facette::getPointArray() const {
		return m_pointArray;
	}

	void Facette::draw() const {
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.x, m_color.y, m_color.z);
		//this is this call which  provok problem with severall instances of the cube
		LeapUtilGL::drawFacet(LeapUtilGL::eStyle::kStyle_Solid, *m_pointArray[0], *m_pointArray[1], *m_pointArray[2]);
	}
}