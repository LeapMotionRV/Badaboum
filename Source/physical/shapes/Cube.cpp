#include "Cube.h"

namespace physical
{

	Cube::Cube(physical::ParticleManager* pParticuleManager)
	{
		m_cubeGraph = new ParticleGraph();
		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.2f;
		glm::vec3 force = glm::vec3(0.f);
		glm::vec3 color = glm::vec3(0.1f, 0.f, 0.f);
		m_part1 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 0.f), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part2 = pParticuleManager->addParticle(glm::vec3(1.f, .0f, 0.f), speed, mass, force, glm::vec3(0.2f, 0.f, 0.f));
		m_part3 = pParticuleManager->addParticle(glm::vec3(1.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.3f, 0.f, 0.f));
		m_part4 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.4f, 0.f, 0.f));
		m_part5 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 1.f), speed, mass, force, glm::vec3(0.5f, 0.f, 0.f));
		m_part6 = pParticuleManager->addParticle(glm::vec3(1.f, .0f, 1.f), speed, mass, force, glm::vec3(0.6f, 0.f, 0.f));
		m_part7 = pParticuleManager->addParticle(glm::vec3(1.f, 1.f, 1.f), speed, mass, force, glm::vec3(0.7f, 0.f, 0.f));
		m_part8 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 1.f), speed, mass, force, glm::vec3(0.8f, 0.f, 0.f));
		//face 1
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part2));
		m_cubeGraph->push_back(std::make_pair(m_part2,m_part3));
		m_cubeGraph->push_back(std::make_pair(m_part3,m_part4));
		m_cubeGraph->push_back(std::make_pair(m_part4,m_part1));
		//face 2
		m_cubeGraph->push_back(std::make_pair(m_part5,m_part6));
		m_cubeGraph->push_back(std::make_pair(m_part6,m_part7));
		m_cubeGraph->push_back(std::make_pair(m_part7,m_part8));
		m_cubeGraph->push_back(std::make_pair(m_part5,m_part8));
		//faces 3, 4, 5 and 6
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part5));
		m_cubeGraph->push_back(std::make_pair(m_part4,m_part8));
		m_cubeGraph->push_back(std::make_pair(m_part2,m_part6));
		m_cubeGraph->push_back(std::make_pair(m_part3,m_part7));

		//diagonales interieures
		m_cubeGraph->push_back(std::make_pair(m_part3,m_part5));
		m_cubeGraph->push_back(std::make_pair(m_part2,m_part8));
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part7));
		m_cubeGraph->push_back(std::make_pair(m_part4,m_part6));

		//diagonales faces
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part3));
		m_cubeGraph->push_back(std::make_pair(m_part2,m_part4));
		m_cubeGraph->push_back(std::make_pair(m_part5,m_part7));
		m_cubeGraph->push_back(std::make_pair(m_part6,m_part8));

		m_cubeGraph->push_back(std::make_pair(m_part5,m_part4));
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part8));
		m_cubeGraph->push_back(std::make_pair(m_part6,m_part3));
		m_cubeGraph->push_back(std::make_pair(m_part2,m_part7));

		m_cubeGraph->push_back(std::make_pair(m_part2,m_part5));
		m_cubeGraph->push_back(std::make_pair(m_part1,m_part6));
		m_cubeGraph->push_back(std::make_pair(m_part3,m_part8));
		m_cubeGraph->push_back(std::make_pair(m_part4,m_part7));
	}

	Cube::~Cube()
	{
	}

	void Cube::drawCube(physical::ParticleManager* pParticuleManager){
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part4));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part5),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part5), pParticuleManager->getPosition(m_part4), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part2),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part5));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part4),pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
	}
}