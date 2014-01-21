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
		unsigned int part1 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 0.f), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		unsigned int part2 = pParticuleManager->addParticle(glm::vec3(1.f, .0f, 0.f), speed, mass, force, glm::vec3(0.2f, 0.f, 0.f));
		unsigned int part3 = pParticuleManager->addParticle(glm::vec3(1.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.3f, 0.f, 0.f));
		unsigned int part4 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 0.f), speed, mass, force, glm::vec3(0.4f, 0.f, 0.f));
		unsigned int part5 = pParticuleManager->addParticle(glm::vec3(0.f, 0.f, 1.f), speed, mass, force, glm::vec3(0.5f, 0.f, 0.f));
		unsigned int part6 = pParticuleManager->addParticle(glm::vec3(1.f, .0f, 1.f), speed, mass, force, glm::vec3(0.6f, 0.f, 0.f));
		unsigned int part7 = pParticuleManager->addParticle(glm::vec3(1.f, 1.f, 1.f), speed, mass, force, glm::vec3(0.7f, 0.f, 0.f));
		unsigned int part8 = pParticuleManager->addParticle(glm::vec3(0.f, 1.f, 1.f), speed, mass, force, glm::vec3(0.8f, 0.f, 0.f));
		//face 1
		m_cubeGraph->push_back(std::make_pair(part2,part1));
		m_cubeGraph->push_back(std::make_pair(part2,part3));
		m_cubeGraph->push_back(std::make_pair(part3,part4));
		m_cubeGraph->push_back(std::make_pair(part4,part1));
		//face 2
		m_cubeGraph->push_back(std::make_pair(part6,part5));
		m_cubeGraph->push_back(std::make_pair(part6,part7));
		m_cubeGraph->push_back(std::make_pair(part7,part8));
		m_cubeGraph->push_back(std::make_pair(part5,part8));
		//faces 3, 4, 5 and 6
		/*m_cubeGraph->push_back(std::make_pair(part1,part5));
		m_cubeGraph->push_back(std::make_pair(part8,part4));
		m_cubeGraph->push_back(std::make_pair(part6,part2));
		m_cubeGraph->push_back(std::make_pair(part7,part3));*/
		//diagonales
		/*m_cubeGraph->push_back(std::make_pair(part5,part3));
		m_cubeGraph->push_back(std::make_pair(part2,part8));
		m_cubeGraph->push_back(std::make_pair(part1,part7));
		m_cubeGraph->push_back(std::make_pair(part6,part4));
		*/
	}

	Cube::~Cube()
	{
	}
}