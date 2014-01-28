#include "Cube.h"

#include "../../util/LeapUtilGL.h"

namespace physical
{

	Cube::Cube(ParticleManager* pParticuleManager, float size, glm::vec3 center, glm::vec3 color)
	{
		m_name = "Cube";
		m_size = size;
		m_center = center;
		m_color = color;

		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.2f;
		glm::vec3 force = glm::vec3(0.f);
		float tmpSize = size /2.;

		//near face
		m_part1 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y-tmpSize, center.z-tmpSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part2 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y-tmpSize, center.z-tmpSize), speed, mass, force, glm::vec3(0.2f, 0.f, 0.f));
		m_part3 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y+tmpSize, center.z-tmpSize), speed, mass, force, glm::vec3(0.3f, 0.f, 0.f));
		m_part4 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y+tmpSize, center.z-tmpSize), speed, mass, force, glm::vec3(0.4f, 0.f, 0.f));
		//far face
		m_part5 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y-tmpSize, center.z+tmpSize), speed, mass, force, glm::vec3(0.5f, 0.f, 0.f));
		m_part6 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y-tmpSize, center.z+tmpSize), speed, mass, force, glm::vec3(0.6f, 0.f, 0.f));
		m_part7 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y+tmpSize, center.z+tmpSize), speed, mass, force, glm::vec3(0.7f, 0.f, 0.f));
		m_part8 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y+tmpSize, center.z+tmpSize), speed, mass, force, glm::vec3(0.8f, 0.f, 0.f));
		//center of faces
		m_part_center1 = pParticuleManager->addParticle(glm::vec3(center.x, center.y, center.z-tmpSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part_center2 = pParticuleManager->addParticle(glm::vec3(center.x, center.y, center.z+tmpSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part_center3 = pParticuleManager->addParticle(glm::vec3(center.x, center.y-tmpSize, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part_center4 = pParticuleManager->addParticle(glm::vec3(center.x, center.y+tmpSize, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part_center5 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		m_part_center6 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));
		
		//face 1
		m_graph->push_back(std::make_pair(m_part1,m_part2));
		m_graph->push_back(std::make_pair(m_part2,m_part3));
		m_graph->push_back(std::make_pair(m_part3,m_part4));
		m_graph->push_back(std::make_pair(m_part4,m_part1));
		//face 2
		m_graph->push_back(std::make_pair(m_part5,m_part6));
		m_graph->push_back(std::make_pair(m_part6,m_part7));
		m_graph->push_back(std::make_pair(m_part7,m_part8));
		m_graph->push_back(std::make_pair(m_part5,m_part8));
		//faces 3, 4, 5 and 6
		m_graph->push_back(std::make_pair(m_part1,m_part5));
		m_graph->push_back(std::make_pair(m_part4,m_part8));
		m_graph->push_back(std::make_pair(m_part2,m_part6));
		m_graph->push_back(std::make_pair(m_part3,m_part7));
		//diagonales interieures
		m_graph->push_back(std::make_pair(m_part3,m_part5));
		m_graph->push_back(std::make_pair(m_part2,m_part8));
		m_graph->push_back(std::make_pair(m_part1,m_part7));
		m_graph->push_back(std::make_pair(m_part4,m_part6));
		//diagonales
		m_graph->push_back(std::make_pair(m_part1,m_part3));
		m_graph->push_back(std::make_pair(m_part2,m_part4));
		m_graph->push_back(std::make_pair(m_part5,m_part7));
		m_graph->push_back(std::make_pair(m_part6,m_part8));

		m_graph->push_back(std::make_pair(m_part5,m_part4));
		m_graph->push_back(std::make_pair(m_part1,m_part8));
		m_graph->push_back(std::make_pair(m_part6,m_part3));
		m_graph->push_back(std::make_pair(m_part2,m_part7));

		m_graph->push_back(std::make_pair(m_part2,m_part5));
		m_graph->push_back(std::make_pair(m_part1,m_part6));
		m_graph->push_back(std::make_pair(m_part3,m_part8));
		m_graph->push_back(std::make_pair(m_part4,m_part7));

		//centers
		//near
		m_graph->push_back(std::make_pair(m_part_center1,m_part1));
		m_graph->push_back(std::make_pair(m_part_center1,m_part2));
		m_graph->push_back(std::make_pair(m_part_center1,m_part3));
		m_graph->push_back(std::make_pair(m_part_center1,m_part4));
		//far
		m_graph->push_back(std::make_pair(m_part_center2,m_part5));
		m_graph->push_back(std::make_pair(m_part_center2,m_part6));
		m_graph->push_back(std::make_pair(m_part_center2,m_part7));
		m_graph->push_back(std::make_pair(m_part_center2,m_part8));
		//left
		m_graph->push_back(std::make_pair(m_part_center3,m_part1));
		m_graph->push_back(std::make_pair(m_part_center3,m_part5));
		m_graph->push_back(std::make_pair(m_part_center3,m_part4));
		m_graph->push_back(std::make_pair(m_part_center3,m_part7));
		//right
		m_graph->push_back(std::make_pair(m_part_center4,m_part2));
		m_graph->push_back(std::make_pair(m_part_center4,m_part6));
		m_graph->push_back(std::make_pair(m_part_center4,m_part3));
		m_graph->push_back(std::make_pair(m_part_center4,m_part8));
		//top
		m_graph->push_back(std::make_pair(m_part_center5,m_part4));
		m_graph->push_back(std::make_pair(m_part_center5,m_part3));
		m_graph->push_back(std::make_pair(m_part_center5,m_part7));
		m_graph->push_back(std::make_pair(m_part_center5,m_part8));
		//bottom
		m_graph->push_back(std::make_pair(m_part_center6,m_part1));
		m_graph->push_back(std::make_pair(m_part_center6,m_part2));
		m_graph->push_back(std::make_pair(m_part_center6,m_part5));
		m_graph->push_back(std::make_pair(m_part_center6,m_part6));
	}

	Cube::~Cube()
	{
	}

	void Cube::draw(physical::ParticleManager* pParticuleManager){
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.r, m_color.g, m_color.b);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part4));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part5),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part5), pParticuleManager->getPosition(m_part4), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part2),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part5));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part4),pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
	}
}