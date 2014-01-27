#include "Line.h"

#include "../../util/LeapUtilGL.h"

namespace physical
{

	Line::Line(physical::ParticleManager* pParticuleManager)
	{
		m_name = "Line";
		m_color = glm::vec3(0.5f, 0.5f, 0.5f);

		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.1f;
		glm::vec3 force = glm::vec3(0.f);
		m_part1 = pParticuleManager->addParticle(glm::vec3(0.f, 2.f, 0.f), speed, mass, force, glm::vec3(1.f, 0.f, 0.f));
		m_part2 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
		m_part3 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 0.f), speed, mass, force, glm::vec3(0.f, 0.f, 1.f));
		
		m_graph->push_back(std::make_pair(m_part1, m_part2));
		m_graph->push_back(std::make_pair(m_part2, m_part3));
		m_graph->push_back(std::make_pair(m_part1, m_part3));
	}

	void Line::draw(ParticleManager* pParticuleManager){
	}
}