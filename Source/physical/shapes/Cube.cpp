#include "Cube.h"

#include "../../util/LeapUtilGL.h"

namespace physical
{

	Cube::Cube(physical::ParticleManager* pParticuleManager, float size, glm::vec3 center, size_t discFactor, glm::vec3 color)
	{
		m_name = "Cube";
		m_size = size;
		m_center = center;
		m_discFactor = discFactor;
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

		//add particles on each face, depends on the discFactor
		float disc = size / discFactor;
		for(float i = 0.f; i < size; i+= disc){
			for(float j = 0.f; j < size; j+= disc){
				//near + far
				unsigned int p1 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize+i, center.y-tmpSize+j, center.z-tmpSize), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				unsigned int p2 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize+i, center.y-tmpSize+j, center.z+tmpSize), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				if(i<tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part1,p1));
					m_graph->push_back(std::make_pair(m_part5,p2));
				}
				else if(i>tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part2,p1));
					m_graph->push_back(std::make_pair(m_part6,p2));
				}
				else if(i>tmpSize && j>tmpSize){
					m_graph->push_back(std::make_pair(m_part3,p1));
					m_graph->push_back(std::make_pair(m_part7,p2));
				}
				else{
					m_graph->push_back(std::make_pair(m_part4,p1));
					m_graph->push_back(std::make_pair(m_part8,p2));
				}
				//right + left
				unsigned int p3 = pParticuleManager->addParticle(glm::vec3(center.x+tmpSize, center.y-tmpSize+j, center.z-tmpSize+i), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				unsigned int p4 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize, center.y-tmpSize+j, center.z-tmpSize+i), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				if(i<tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part2,p3));
					m_graph->push_back(std::make_pair(m_part1,p4));
				}
				else if(i>tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part6,p3));
					m_graph->push_back(std::make_pair(m_part5,p4));
				}
				else if(i>tmpSize && j>tmpSize){
					m_graph->push_back(std::make_pair(m_part7,p3));
					m_graph->push_back(std::make_pair(m_part8,p4));
				}
				else{
					m_graph->push_back(std::make_pair(m_part3,p3));
					m_graph->push_back(std::make_pair(m_part4,p4));
				}
				//top + bottom
				unsigned int p5 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize+i, center.y+tmpSize, center.z-tmpSize+j), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				unsigned int p6 = pParticuleManager->addParticle(glm::vec3(center.x-tmpSize+i, center.y-tmpSize, center.z-tmpSize+j), speed, mass, force, glm::vec3(0.f, 1.f, 0.f));
				if(i<tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part4,p5));
					m_graph->push_back(std::make_pair(m_part1,p6));
				}
				else if(i>tmpSize && j<tmpSize){
					m_graph->push_back(std::make_pair(m_part3,p5));
					m_graph->push_back(std::make_pair(m_part2,p6));
				}
				else if(i>tmpSize && j>tmpSize){
					m_graph->push_back(std::make_pair(m_part7,p5));
					m_graph->push_back(std::make_pair(m_part6,p6));
				}
				else{
					m_graph->push_back(std::make_pair(m_part8,p5));
					m_graph->push_back(std::make_pair(m_part5,p6));
				}
			}
		}
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