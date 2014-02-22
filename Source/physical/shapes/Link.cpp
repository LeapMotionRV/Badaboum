#include "Link.h"
#include "../../util/LeapUtilGL.h"


namespace physical
{
	//rigidity
	float Link::m_K = 2.f;
	//brake
	float Link::m_V = 0.0001f;

	Link::Link(ParticleManager* pm, size_t idParticle1, size_t idParticle2)
	{
		//create links
		m_graph->push_back(std::make_pair(idParticle1, idParticle2));

		glm::vec3 pos1 = pm->getPosition(idParticle1);
		glm::vec3 pos2 = pm->getPosition(idParticle2);
		//lenght of springs
		m_L = glm::length(pos2 - pos1);
	}

	void Link::applyInternalForces(ParticleManager* pm, float dt){
		unsigned int idParticle1 = m_graph[0][0].first;
		unsigned int idParticle2 = m_graph[0][0].second;

		glm::vec3 link1_pos1 = pm->getPosition(idParticle1);
		glm::vec3 link1_pos2 = pm->getPosition(idParticle2);

		//idParticle1
		pm->addForceToParticle(getHookForce(m_K, m_L, link1_pos1, link1_pos2), idParticle1);
		pm->addForceToParticle(getBrakeForce(m_V, dt, link1_pos1, link1_pos2), idParticle1);

		//idParticle1=2
		pm->addForceToParticle(-getHookForce(m_K, m_L, link1_pos1, link1_pos2), idParticle2);
		pm->addForceToParticle(-getBrakeForce(m_V, dt, link1_pos1, link1_pos2), idParticle2);
	}

	
	void Link::applyExternalForces(ParticleManager* pParticleManager, float dt){
		return;
	}

	void Link::draw(ParticleManager* pParticuleManager){
		glm::vec3 p1 = pParticuleManager->getPositionArray()[m_graph[0][0].first];
		glm::vec3 p2 = pParticuleManager->getPositionArray()[m_graph[0][0].second];
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, glm::vec3(p1.x-0.01f,p1.y-0.01f,p1.z-0.01f), glm::vec3(p1.x+0.01f,p1.y+0.01f,p1.z+0.01f), glm::vec3(p2.x-0.01f,p2.y-0.01f,p2.z-0.01f), glm::vec3(p2.x+0.01f,p2.y+0.01f,p2.z+0.01f));
	}
}