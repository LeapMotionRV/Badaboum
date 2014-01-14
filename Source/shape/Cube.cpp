#include "Cube.h"


Cube::Cube(physical::ParticleManager &pm)
{
	m_cubeGraph = physical::ParticleGraph();
	unsigned int part1 = pm.addParticle(glm::vec3(0.5f, 1.f, 0.f), glm::vec3(0.f), 0.05f, glm::vec3(0.f), glm::vec3(1.f, 0.5f, 0.2f));
	unsigned int part2 = pm.addParticle(glm::vec3(1.f, 0.5f, 0.f), glm::vec3(0.f), 0.05f, glm::vec3(0.f), glm::vec3(1.f, 0.0f, 0.0f));
	m_cubeGraph.push_back(std::make_pair(part1,part2));
}

Cube::~Cube()
{
}
