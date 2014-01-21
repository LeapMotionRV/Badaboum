#include "Line.h"

namespace physical
{

	Line::Line(physical::ParticleManager* pParticuleManager)
	{
		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.1f;
		glm::vec3 force = glm::vec3(0.f);
		unsigned int part1 = pParticuleManager->addParticle(glm::vec3(0.f, 2.f, 0.f), speed, mass, force, glm::vec3(1.f, 0.f, 0.f));
		unsigned int part2 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
		unsigned int part3 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 0.f), speed, mass, force, glm::vec3(0.f, 0.f, 1.f));
		m_graph->push_back(std::make_pair(part1,part2));
		m_graph->push_back(std::make_pair(part2,part3));
		m_graph->push_back(std::make_pair(part1,part3));
	}
}