#include "Ground.h"

namespace physical 
{
	Ground::Ground(LeapfrogSolver* pLeapfrogSolver){
		m_pLeapfrogSolver = pLeapfrogSolver;
		m_polygonArray = std::vector<Polygon*>();
		m_polygonForceArray = std::vector<PolygonForce*>();
	}

	Ground::~Ground(){
		for(unsigned int i = 0; i <= m_polygonArray.size()-1; ++i){
			delete m_polygonArray[i];
			delete m_polygonForceArray[i];
		}
	}

	void Ground::addPolygonAndForce(Polygon* pPolygon, PolygonForce* pPolygonForce) {
		m_polygonArray.push_back(pPolygon);
		m_polygonForceArray.push_back(pPolygonForce);
	}

	void Ground::addPolygonAndForce(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 pos4, glm::vec3 color, float elasticity){
		Polygon* ground = new Polygon(pos1, pos2, pos3, pos4, color);
		PolygonForce* polygonForce = new PolygonForce(ground, elasticity, m_pLeapfrogSolver);
		this->addPolygonAndForce(ground, polygonForce);
	}

	void Ground::apply(ParticleManager* pm, float dt){
		for(unsigned int i = 0; i <= m_polygonForceArray.size()-1; ++i){
			m_polygonForceArray[i]->setDt(dt);
			m_polygonForceArray[i]->apply(pm);
		}
	}

	void Ground::createTexture() {
		juce::File fileGround = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/textureGround.png");
		if(!fileGround.existsAsFile()){
			std::cout << "Error" << std::endl;
		}
		else {
			juce::Image imageGround = juce::ImageCache::getFromFile(fileGround);
			loadImage(imageGround);
		}
	}

	void Ground::draw(){
		for(unsigned int i = 0; i <= m_polygonForceArray.size()-1; ++i){
			bind();
			m_polygonArray[i]->draw();
			unbind();
		}
	}
}