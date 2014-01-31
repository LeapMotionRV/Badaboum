#include "Cube.h"
#include "../../util/LeapUtilGL.h"


namespace physical
{
	Cube::Cube(ParticleManager* pParticuleManager, float size, glm::vec3 center, glm::vec3 color)
	{
		m_size = size;//size of edges
		m_center = center;
		m_color = color;

		//lenght of springs
		m_L0.x = size;
		m_L0.y = size;
		m_L0.z = size;
		float size_diag = size * sqrt(2.f);
		m_L1 = size_diag;
		m_L2 = size_diag/2.f;
		m_L3 = size * sqrt(3.f);

		//rigidity
		float coeffK = 3.f;
		m_K0 = coeffK * m_L0.x;
		/*m_K1 = 1.f;
		m_K2 = 1.f;
		m_K3 = 1.f;*/
		m_K1 = coeffK * m_L1;
		m_K2 = coeffK * m_L2;
		m_K3 = coeffK * m_L3;

		//brake
		float coef = 0.001;
		m_V0 = coef;
		/*m_V1 = 0.001f;
		m_V2 = 0.001f;
		m_V3 = 0.001f;*/
		m_V1 = coef;
		m_V2 = coef;
		m_V3 = coef;

		//create particles
		glm::vec3 speed = glm::vec3(0.f);
		float mass = 0.2f;
		glm::vec3 force = glm::vec3(0.f);
		float halfSize = size /2.f;
		//far face
		m_part1 = pParticuleManager->addParticle(glm::vec3(center.x-halfSize, center.y-halfSize, center.z-halfSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));//particul placed in far bottom left
		m_part2 = pParticuleManager->addParticle(glm::vec3(center.x+halfSize, center.y-halfSize, center.z-halfSize), speed, mass, force, glm::vec3(0.2f, 0.f, 0.f));//particul placed in far bottom right
		m_part3 = pParticuleManager->addParticle(glm::vec3(center.x+halfSize, center.y+halfSize, center.z-halfSize), speed, mass, force, glm::vec3(0.3f, 0.f, 0.f));//particul placed in far top right
		m_part4 = pParticuleManager->addParticle(glm::vec3(center.x-halfSize, center.y+halfSize, center.z-halfSize), speed, mass, force, glm::vec3(0.4f, 0.f, 0.f));//particul placed in far top left
		//near face
		m_part5 = pParticuleManager->addParticle(glm::vec3(center.x-halfSize, center.y-halfSize, center.z+halfSize), speed, mass, force, glm::vec3(0.5f, 0.f, 0.f));//particul placed in near bottom left
		m_part6 = pParticuleManager->addParticle(glm::vec3(center.x+halfSize, center.y-halfSize, center.z+halfSize), speed, mass, force, glm::vec3(0.6f, 0.f, 0.f));//particul placed in near bottom right
		m_part7 = pParticuleManager->addParticle(glm::vec3(center.x+halfSize, center.y+halfSize, center.z+halfSize), speed, mass, force, glm::vec3(0.7f, 0.f, 0.f));//particul placed in near top right
		m_part8 = pParticuleManager->addParticle(glm::vec3(center.x-halfSize, center.y+halfSize, center.z+halfSize), speed, mass, force, glm::vec3(0.8f, 0.f, 0.f));//particul placed in near top left
		//center of faces
		m_part_center1 = pParticuleManager->addParticle(glm::vec3(center.x, center.y, center.z-halfSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));//far face
		m_part_center2 = pParticuleManager->addParticle(glm::vec3(center.x, center.y, center.z+halfSize), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));//near face
		m_part_center3 = pParticuleManager->addParticle(glm::vec3(center.x, center.y-halfSize, center.z), speed, mass, force, glm::vec3(1.f, 1.f, 1.f));//bottom face
		m_part_center4 = pParticuleManager->addParticle(glm::vec3(center.x, center.y+halfSize, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));//top face
		m_part_center5 = pParticuleManager->addParticle(glm::vec3(center.x-halfSize, center.y, center.z), speed, mass, force, glm::vec3(1.f, 1.f, 1.f));//left face
		m_part_center6 = pParticuleManager->addParticle(glm::vec3(center.x+halfSize, center.y, center.z), speed, mass, force, glm::vec3(0.1f, 0.f, 0.f));//right face
	
		//create facets (not verified)
		//far face
		this->addFacet(pParticuleManager, m_part1, m_part_center1, m_part2);
		this->addFacet(pParticuleManager, m_part2, m_part_center1, m_part3);
		this->addFacet(pParticuleManager, m_part3, m_part_center1, m_part4);
		this->addFacet(pParticuleManager, m_part4, m_part_center1, m_part1);
		//near face 
		this->addFacet(pParticuleManager, m_part5, m_part_center2, m_part6);
		this->addFacet(pParticuleManager, m_part6, m_part_center2, m_part7);
		this->addFacet(pParticuleManager, m_part7, m_part_center2, m_part8);
		this->addFacet(pParticuleManager, m_part8, m_part_center2, m_part5);
		//bottom face
		this->addFacet(pParticuleManager, m_part5, m_part_center3, m_part6);
		this->addFacet(pParticuleManager, m_part6, m_part_center3, m_part2);
		this->addFacet(pParticuleManager, m_part2, m_part_center3, m_part1);
		this->addFacet(pParticuleManager, m_part1, m_part_center3, m_part5);
		//top face
		this->addFacet(pParticuleManager, m_part8, m_part_center4, m_part7);
		this->addFacet(pParticuleManager, m_part7, m_part_center4, m_part3);
		this->addFacet(pParticuleManager, m_part3, m_part_center4, m_part4);
		this->addFacet(pParticuleManager, m_part4, m_part_center4, m_part8);
		//left face
		this->addFacet(pParticuleManager, m_part5, m_part_center5, m_part1);
		this->addFacet(pParticuleManager, m_part1, m_part_center5, m_part4);
		this->addFacet(pParticuleManager, m_part4, m_part_center5, m_part8);
		this->addFacet(pParticuleManager, m_part8, m_part_center5, m_part5);
		//right face
		this->addFacet(pParticuleManager, m_part6, m_part_center6, m_part2);
		this->addFacet(pParticuleManager, m_part2, m_part_center6, m_part3);
		this->addFacet(pParticuleManager, m_part3, m_part_center6, m_part7);
		this->addFacet(pParticuleManager, m_part7, m_part_center6, m_part6);

		//create links
		//edges X
		m_graph->push_back(std::make_pair(m_part1,m_part2));
		m_graph->push_back(std::make_pair(m_part4,m_part3));//did the order matter ? (Arthur question for Clement)
		m_graph->push_back(std::make_pair(m_part5,m_part6));
		m_graph->push_back(std::make_pair(m_part8,m_part7));
		//edges Y
		m_graph->push_back(std::make_pair(m_part1,m_part4));
		m_graph->push_back(std::make_pair(m_part2,m_part3));
		m_graph->push_back(std::make_pair(m_part5,m_part8));
		m_graph->push_back(std::make_pair(m_part6,m_part7));
		//edges Z
		m_graph->push_back(std::make_pair(m_part1,m_part5));
		m_graph->push_back(std::make_pair(m_part2,m_part6));
		m_graph->push_back(std::make_pair(m_part4,m_part8));
		m_graph->push_back(std::make_pair(m_part3,m_part7));
		//diagonal on each face (maybe useless)
		/*m_graph->push_back(std::make_pair(m_part1,m_part3));
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
		m_graph->push_back(std::make_pair(m_part4,m_part7));*/
		//center diagonals
		//links far face
		m_graph->push_back(std::make_pair(m_part_center1,m_part1));
		m_graph->push_back(std::make_pair(m_part_center1,m_part2));
		m_graph->push_back(std::make_pair(m_part_center1,m_part3));
		m_graph->push_back(std::make_pair(m_part_center1,m_part4));
		//links near face
		m_graph->push_back(std::make_pair(m_part_center2,m_part5));
		m_graph->push_back(std::make_pair(m_part_center2,m_part6));
		m_graph->push_back(std::make_pair(m_part_center2,m_part7));
		m_graph->push_back(std::make_pair(m_part_center2,m_part8));
		//links bottom face
		m_graph->push_back(std::make_pair(m_part_center3,m_part1));
		m_graph->push_back(std::make_pair(m_part_center3,m_part2));
		m_graph->push_back(std::make_pair(m_part_center3,m_part5));
		m_graph->push_back(std::make_pair(m_part_center3,m_part6));
		//links top face
		m_graph->push_back(std::make_pair(m_part_center4,m_part3));
		m_graph->push_back(std::make_pair(m_part_center4,m_part4));
		m_graph->push_back(std::make_pair(m_part_center4,m_part7));
		m_graph->push_back(std::make_pair(m_part_center4,m_part8));
		//links left face
		m_graph->push_back(std::make_pair(m_part_center5,m_part4));
		m_graph->push_back(std::make_pair(m_part_center5,m_part5));
		m_graph->push_back(std::make_pair(m_part_center5,m_part7));
		m_graph->push_back(std::make_pair(m_part_center5,m_part8));
		//links right face
		m_graph->push_back(std::make_pair(m_part_center6,m_part2));
		m_graph->push_back(std::make_pair(m_part_center6,m_part3));
		m_graph->push_back(std::make_pair(m_part_center6,m_part6));
		m_graph->push_back(std::make_pair(m_part_center6,m_part7));
		//intern diagonals
		m_graph->push_back(std::make_pair(m_part3,m_part5));
		m_graph->push_back(std::make_pair(m_part2,m_part8));
		m_graph->push_back(std::make_pair(m_part1,m_part7));
		m_graph->push_back(std::make_pair(m_part4,m_part6));
	}

	void Cube::applyInternalForces(ParticleManager* pParticleManager, float dt){
		for(unsigned int k = 0; k < m_graph->size(); ++k){
			unsigned int id1 = (*m_graph)[k].first;
			unsigned int id2 = (*m_graph)[k].second;

			glm::vec3 pos1 = pParticleManager->getPosition(id1);
			glm::vec3 pos2 = pParticleManager->getPosition(id2);

			bool isEdgeX = ((k < 4) ? true : false);
			bool isEdgeY = ((k > 3 && k < 8) ? true : false);
			bool isEdgeZ = ((k > 7 && k < 12) ? true : false);
			/*bool isDiagFace = ((k > 11 && k < 24) ? true : false);
			bool isDiagCenterFace = ((k > 23 && k < 48) ? true : false);
			bool isDiagIntern = ((k > 47 && k < 52) ? true : false);*/
			bool isDiagCenterFace = ((k > 11 && k < 36) ? true : false);
			bool isDiagIntern = ((k > 35 && k < 40) ? true : false);

			if(isEdgeX){
				pParticleManager->addForceToParticle(getHookForce(m_K0, m_L0.x, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K0, m_L0.x, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V0, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V0, dt, pos1, pos2), id2);
			}
			else if(isEdgeY){
				pParticleManager->addForceToParticle(getHookForce(m_K0, m_L0.y, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K0, m_L0.y, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V0, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V0, dt, pos1, pos2), id2);
			}
			else if(isEdgeZ){
				pParticleManager->addForceToParticle(getHookForce(m_K0, m_L0.z, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K0, m_L0.z, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V0, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V0, dt, pos1, pos2), id2);
			}
			/*else if(isDiagFace){
				pParticleManager->addForceToParticle(getHookForce(m_K1, m_L1, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K1, m_L1, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V1, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V1, dt, pos1, pos2), id2);  
			}*/
			else if(isDiagCenterFace){
				pParticleManager->addForceToParticle(getHookForce(m_K2, m_L2, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K2, m_L2, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V2, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V2, dt, pos1, pos2), id2);
			}
			else if(isDiagIntern){
				pParticleManager->addForceToParticle(getHookForce(m_K3, m_L3, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getHookForce(m_K3, m_L3, pos1, pos2), id2);
				pParticleManager->addForceToParticle(getBrakeForce(m_V3, dt, pos1, pos2), id1);
				pParticleManager->addForceToParticle(-getBrakeForce(m_V3, dt, pos1, pos2), id2);
			}
			else{
				std::cerr << "The link is impossible for the cube" << std::endl;
			}
		}
	}

	void Cube::drawWithFacets(physical::ParticleManager* pParticuleManager){
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.r, m_color.g, m_color.b);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part4));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part5),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part5), pParticuleManager->getPosition(m_part4), pParticuleManager->getPosition(m_part8));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part2),pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part1),pParticuleManager->getPosition(m_part2), pParticuleManager->getPosition(m_part6), pParticuleManager->getPosition(m_part5));
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, pParticuleManager->getPosition(m_part4),pParticuleManager->getPosition(m_part3), pParticuleManager->getPosition(m_part7), pParticuleManager->getPosition(m_part8));
	}

	void Cube::addFacet(ParticleManager* pParticleManager, unsigned int firstPoint, unsigned int secondPoint, unsigned int thirdPoint){
		Facette facet = Facette(pParticleManager->getPointeurOnPosition(firstPoint), pParticleManager->getPointeurOnPosition(secondPoint), pParticleManager->getPointeurOnPosition(thirdPoint), m_color);
		m_facets.push_back(facet);
	}

	void Cube::draw(physical::ParticleManager* pParticuleManager){
		LeapUtilGL::GLMatrixScope gridMatrixScope;
		glColor3f(m_color.r, m_color.g, m_color.b);
		for(unsigned int i = 0; i < this->getFacets().size(); ++i){
			LeapUtilGL::drawFacet(LeapUtilGL::eStyle::kStyle_Solid,*this->getFacets()[i].getPointArray()[0], *this->getFacets()[i].getPointArray()[1], *this->getFacets()[i].getPointArray()[2]);
		}
	}

}