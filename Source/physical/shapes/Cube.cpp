#include "Cube.h"

namespace physical
{
	Cube::Cube(physical::ParticleManager* pParticuleManager)
	{
		m_cubeGraph = ParticleGraph();
		unsigned int part1 = pParticuleManager->addParticle(glm::vec3(0.5f, 1.f, 0.f), glm::vec3(0.f), 0.05f, glm::vec3(0.f), glm::vec3(1.f, 0.5f, 0.2f));
		unsigned int part2 = pParticuleManager->addParticle(glm::vec3(1.f, 0.5f, 0.f), glm::vec3(0.f), 0.05f, glm::vec3(0.f), glm::vec3(1.f, 0.0f, 0.0f));
		m_cubeGraph.push_back(std::make_pair(part1,part2));
	}

	Cube::~Cube()
	{
	}
}