#include "Line.h"
#include "../../util/LeapUtilGL.h"


namespace physical
{
	Line::Line(ParticleManager* pParticuleManager, float size, glm::vec3 startedPoint)
	{
		m_size = size;
		m_startedPoint = startedPoint;
		m_color = glm::vec3(0.5f, 0.5f, 0.5f);

		//lenght of springs
		m_L.x = size;
		m_L.y = size;
		m_L.z = size;

		//rigidity
		m_K = 0.5f;

		//brake
		m_V = 0.005f;

		//create particles
		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.1f;
		glm::vec3 force = glm::vec3(0.f);
		m_part1 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y, startedPoint.z), speed, mass, force, m_color);
		m_part2 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y+size, startedPoint.z), speed, mass, force, m_color);
		m_part3 = pParticuleManager->addParticle(glm::vec3(startedPoint.x, startedPoint.y+size, startedPoint.z+size), speed, mass, force, m_color);
		
		//create links
		m_graph->push_back(std::make_pair(m_part1, m_part2));
		m_graph->push_back(std::make_pair(m_part2, m_part3));
		m_graph->push_back(std::make_pair(m_part1, m_part3));
	}

	void Line::applyInternalForces(ParticleManager* pParticleManager, float dt){
		unsigned int link1_id1 = (*m_graph)[0].first;
		unsigned int link1_id2 = (*m_graph)[0].second;
		unsigned int link2_id1 = (*m_graph)[1].first;
		unsigned int link2_id2 = (*m_graph)[1].second;
		unsigned int link3_id1 = (*m_graph)[2].first;
		unsigned int link3_id2 = (*m_graph)[2].second;

		glm::vec3 link1_pos1 = pParticleManager->getPosition(link1_id1);
		glm::vec3 link1_pos2 = pParticleManager->getPosition(link1_id2);
		glm::vec3 link2_pos1 = pParticleManager->getPosition(link2_id1);
		glm::vec3 link2_pos2 = pParticleManager->getPosition(link2_id2);
		glm::vec3 link3_pos1 = pParticleManager->getPosition(link3_id1);
		glm::vec3 link3_pos2 = pParticleManager->getPosition(link3_id2);

		pParticleManager->addForceToParticle(getHookForce(m_K, m_L.x, link1_pos1, link1_pos2), link1_id1);
		pParticleManager->addForceToParticle(-getHookForce(m_K, m_L.x, link1_pos1, link1_pos2), link1_id2);
		pParticleManager->addForceToParticle(getBrakeForce(m_V, dt, link1_pos1, link1_pos2), link1_id1);
		pParticleManager->addForceToParticle(-getBrakeForce(m_V, dt, link1_pos1, link1_pos2), link1_id2);

		pParticleManager->addForceToParticle(getHookForce(m_K, m_L.x, link2_pos1, link2_pos2), link2_id1);
		pParticleManager->addForceToParticle(-getHookForce(m_K, m_L.x, link2_pos1, link2_pos2), link2_id2);
		pParticleManager->addForceToParticle(getBrakeForce(m_V, dt, link2_pos1, link2_pos2), link2_id1);
		pParticleManager->addForceToParticle(-getBrakeForce(m_V, dt, link2_pos1, link2_pos2), link2_id2);

		pParticleManager->addForceToParticle(getHookForce(m_K, m_L.x, link3_pos1, link3_pos2), link3_id1);
		pParticleManager->addForceToParticle(-getHookForce(m_K, m_L.x, link3_pos1, link3_pos2), link3_id2);
		pParticleManager->addForceToParticle(getBrakeForce(m_V, dt, link3_pos1, link3_pos2), link3_id1);
		pParticleManager->addForceToParticle(-getBrakeForce(m_V, dt, link3_pos1, link3_pos2), link3_id2);
	}

	
	void Line::applyExternalForces(ParticleManager* pParticleManager, float dt){
		return;
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