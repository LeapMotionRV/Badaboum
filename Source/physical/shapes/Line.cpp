#include "Line.h"

#include "../../util/LeapUtilGL.h"

namespace physical
{

	Line::Line(ParticleManager* pParticuleManager, float size, glm::vec3 startedPoint)
	{
		m_name = "Line";
		m_size = size;
		m_startedPoint = startedPoint;
		m_color = glm::vec3(0.5f, 0.5f, 0.5f);

		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.1f;
		glm::vec3 force = glm::vec3(0.f);
		m_part1 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y, startedPoint.z), speed, mass, force, m_color);
		m_part2 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y+size, startedPoint.z), speed, mass, force, m_color);
		m_part3 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y+size, startedPoint.z+size), speed, mass, force, m_color);
		
		m_graph->push_back(std::make_pair(m_part1, m_part2));
		m_graph->push_back(std::make_pair(m_part2, m_part3));
		m_graph->push_back(std::make_pair(m_part1, m_part3));
	}

	void Line::draw(ParticleManager* pParticuleManager){
		//get the 3 particles of the line
		glm::vec3 p1 = pParticuleManager->getPositionArray()[m_part1];
		glm::vec3 p2 = pParticuleManager->getPositionArray()[m_part2];
		glm::vec3 p3 = pParticuleManager->getPositionArray()[m_part3];
		
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, glm::vec3(p1.x-0.01f,p1.y-0.01f,p1.z-0.01f), glm::vec3(p1.x+0.01f,p1.y+0.01f,p1.z+0.01f), glm::vec3(p2.x-0.01f,p2.y-0.01f,p2.z-0.01f), glm::vec3(p2.x+0.01f,p2.y+0.01f,p2.z+0.01f));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, glm::vec3(p2.x-0.01f,p2.y-0.01f,p2.z-0.01f), glm::vec3(p2.x+0.01f,p2.y+0.01f,p2.z+0.01f), glm::vec3(p3.x-0.01f,p3.y-0.01f,p3.z-0.01f), glm::vec3(p3.x+0.01f,p3.y+0.01f,p3.z+0.01f));
	}
}