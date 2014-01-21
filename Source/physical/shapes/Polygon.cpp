#include <math.h>
#include <iostream>

#include "Polygon.h"
#include "../../util/LeapUtilGL.h"


namespace physical 
{
	Polygon::Polygon() {
		m_color = glm::vec3(0.f, 0.f, 1.f);
		m_bIsInner = false;
		m_width = 0;
		m_height = 0;
	}

	Polygon::Polygon(glm::vec3 color, glm::vec3 position, float width, float height, bool isInner) {
		m_color = color;
		m_bIsInner = isInner;
		m_pointArray.push_back(position);
		m_pointArray.push_back(glm::vec3(position.x + width, position.y, position.z));
		m_pointArray.push_back(glm::vec3(position.x + width, position.y, position.z + height));
		m_pointArray.push_back(glm::vec3(position.x, position.y, position.z + height));
		m_width = width;
		m_height = height;
	}

	std::vector<glm::vec3> Polygon::getPointArray() const {
		return m_pointArray;
	}

	void Polygon::draw() const {
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.x, m_color.y, m_color.z);
		glTranslatef(m_pointArray[0].x,  m_pointArray[0].y, m_pointArray[0].z);
		LeapUtilGL::drawQuad(LeapUtilGL::eStyle::kStyle_Solid, LeapUtilGL::ePlane::kPlane_ZX, m_width, m_height);
	}
	
	bool Polygon::isInner() const{
		return m_bIsInner;
	}
}