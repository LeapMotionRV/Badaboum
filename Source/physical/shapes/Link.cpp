#include "Link.h"
#include "../../util/LeapUtilGL.h"
#include "../LinkManager.h"

namespace physical
{
	//rigidity
	float Link::s_K = 2.f; //35.f
	//brake
	float Link::s_V = 0.0001f;//0.001f

	Link::Link(ParticleManager* pm, size_t idParticle1, size_t idParticle2){
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

		glm::vec3 link_pos1 = pm->getPosition(idParticle1);
		glm::vec3 link_pos2 = pm->getPosition(idParticle2);

		//idParticle1
		pm->addForceToParticle(getHookForce(s_K, m_L, link_pos1, link_pos2), idParticle1);
		pm->addForceToParticle(getBrakeForce(s_V, dt, link_pos1, link_pos2), idParticle1);

		//idParticle1=2
		pm->addForceToParticle(-getHookForce(s_K, m_L, link_pos1, link_pos2), idParticle2);
		pm->addForceToParticle(-getBrakeForce(s_V, dt, link_pos1, link_pos2), idParticle2);
	}

	
	void Link::applyExternalForces(ParticleManager*, float){//pParticleManager, dt
		return;
	}

	bool Link::isValid(ParticleManager* pParticleManager) const {
		unsigned int idParticle1 = m_graph[0][0].first;
		unsigned int idParticle2 = m_graph[0][0].second;

		glm::vec3 link_pos1 = pParticleManager->getPosition(idParticle1);
		glm::vec3 link_pos2 = pParticleManager->getPosition(idParticle2);

		return (glm::length(link_pos2 - link_pos1) < (2*LinkManager::getMaxLenghtToCreateLink())) ? true : false;
	}

	void Link::draw(ParticleManager* pParticuleManager){
		glm::vec3 p1 = pParticuleManager->getPositionArray()[m_graph[0][0].first];
		glm::vec3 p2 = pParticuleManager->getPositionArray()[m_graph[0][0].second];
		glColor3f(LinkManager::getColorOfLinks().x, LinkManager::getColorOfLinks().y, LinkManager::getColorOfLinks().z);
		/*LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, 
			glm::vec3(p1.x-0.01f,p1.y-0.01f,p1.z-0.01f), 
			glm::vec3(p1.x+0.01f,p1.y+0.01f,p1.z+0.01f), 
			glm::vec3(p2.x-0.01f,p2.y-0.01f,p2.z-0.01f), 
			glm::vec3(p2.x+0.01f,p2.y+0.01f,p2.z+0.01f)
			);*/
		LeapUtilGL::drawCylinder(LeapUtilGL::eStyle::kStyle_Solid,p1, p2, 0.05);
	}
}