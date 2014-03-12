#include <math.h>
#include <iostream>

#include "Polygon.h"
#include "../../util/LeapUtilGL.h"


namespace physical 
{
	Polygon::Polygon() {
		m_color = glm::vec3(0.f, 0.f, 1.f);
		m_width = 0;
		m_height = 0;
	}

	Polygon::Polygon(glm::vec3 positionTopLeft, glm::vec3 positionTopRight, glm::vec3 positionBottomLeft, glm::vec3 positionBottomRight, glm::vec3 color) {
		m_color = color;
		m_pointArray.push_back(positionTopLeft);
		m_pointArray.push_back(positionTopRight);
		m_pointArray.push_back(positionBottomLeft);
		m_pointArray.push_back(positionBottomRight);
	}

	std::vector<glm::vec3> Polygon::getPointArray() const {
		return m_pointArray;
	}

	void Polygon::draw() const {
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, m_pointArray[0], m_pointArray[1], m_pointArray[2], m_pointArray[3]);
	}
}