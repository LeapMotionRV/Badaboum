#include "Shape.h"


namespace physical
{
	Shape::Shape()
	{
		m_graph = new ParticleGraph();
	}

	Shape::~Shape()
	{
	}

	glm::vec3 Shape::getHookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2) {
		static const float epsilon = 0.0001f;
		glm::vec3 P1P2 = P2 - P1;
		float dP1P2 = glm::length(P1P2);
		glm::vec3 hookForce = K * (1-(L / std::max (dP1P2, epsilon))) * (P1P2);
		return hookForce;
	}

	glm::vec3 Shape::getBrakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2) {
		return V * ((v2 - v1)/dt);
	}
}