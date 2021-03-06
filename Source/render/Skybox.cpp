#include "Skybox.h"


namespace render
{
	Skybox::Skybox(){
		m_pSkyboxUp = new OpenGLTexture();
		m_pSkyboxDown = new OpenGLTexture();
		m_pSkyboxLeft = new OpenGLTexture();
		m_pSkyboxRight = new OpenGLTexture();
		m_pSkyboxForward = new OpenGLTexture();
		m_pSkyboxBack = new OpenGLTexture();
	}

	Skybox::~Skybox(){
		delete m_pSkyboxUp;
		delete m_pSkyboxDown;
		delete m_pSkyboxLeft;
		delete m_pSkyboxRight;
		delete m_pSkyboxForward;
		delete m_pSkyboxBack;
	}

	void Skybox::createTexture() {
		//Up
		juce::File fileSkyboxUp = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/hellTop.jpg");
		if(!fileSkyboxUp.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxUp." << std::endl;
		}
		else {
			juce::Image imageSkyboxUp = juce::ImageCache::getFromFile(fileSkyboxUp);
			m_pSkyboxUp->loadImage(imageSkyboxUp);
		}
		//Down
		juce::File fileSkyboxDown = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/skyboxDown.png");
		if(!fileSkyboxDown.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxDown." << std::endl;
		}
		else {
			juce::Image imageSkyboxDown = juce::ImageCache::getFromFile(fileSkyboxDown);
			m_pSkyboxDown->loadImage(imageSkyboxDown);
		}
		//Left
		juce::File fileSkyboxLeft = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/hellLeft2.jpg");
		if(!fileSkyboxLeft.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxLeft." << std::endl;
		}
		else {
			juce::Image imageSkyboxLeft = juce::ImageCache::getFromFile(fileSkyboxLeft);
			m_pSkyboxLeft->loadImage(imageSkyboxLeft);
		}
		//Right
		juce::File fileSkyboxRight = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/hellRight2.jpg");
		if(!fileSkyboxRight.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxRight." << std::endl;
		}
		else {
			juce::Image imageSkyboxRight = juce::ImageCache::getFromFile(fileSkyboxRight);
			m_pSkyboxRight->loadImage(imageSkyboxRight);
		}
		//Forward
		juce::File fileSkyboxForward = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/hellFront2.jpg");
		if(!fileSkyboxForward.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxForward." << std::endl;
		}
		else {
			juce::Image imageSkyboxForward = juce::ImageCache::getFromFile(fileSkyboxForward);
			m_pSkyboxForward->loadImage(imageSkyboxForward);
		}
		//Back
		juce::File fileSkyboxBack = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/hellBack2.jpg");
		if(!fileSkyboxBack.existsAsFile()){
			std::cout << "Error when loading texture of the skyboxBack." << std::endl;
		}
		else {
			juce::Image imageSkyboxBack = juce::ImageCache::getFromFile(fileSkyboxBack);
			m_pSkyboxBack->loadImage(imageSkyboxBack);
		}
	}

	//Warning to our situation, we moove the scene and not the camera, so the skybox has to be submitted to the rotation, but not to the translation of the scene and not to the scale ? 
	void Skybox::draw(Leap::Matrix rotationMatrix, Leap::Vector totalTranslation, float totalScale){
		//clear color
		glColor3f(1, 1, 1);

		LeapUtilGL::GLMatrixScope skyboxScope;

		int width = m_pSkyboxForward->getWidth();
		int height = m_pSkyboxForward->getHeight();
		float factor = 15.f;
		// Forward
		m_pSkyboxForward->bind();
		glm::vec3 firstPoint = glm::vec3(width/2.f, -height/2.f, -width/2.f);
		glm::vec3 secondPoint = glm::vec3(-width/2.f, -height/2.f, -width/2.f);
		glm::vec3 thirdPoint = glm::vec3(-width/2.f, height/2.f, -width/2.f);
		glm::vec3 forthPoint = glm::vec3(width/2.f, height/2.f, -width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxForward->unbind();
		// Back
		m_pSkyboxBack->bind();
		firstPoint = glm::vec3(width/2.f, -height/2.f, width/2.f);
		secondPoint = glm::vec3(-width/2.f, -height/2.f, width/2.f);
		thirdPoint = glm::vec3(-width/2.f, height/2.f, width/2.f);
		forthPoint = glm::vec3(width/2.f, height/2.f, width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxBack->unbind();
		// Left
		m_pSkyboxLeft->bind();
		firstPoint = glm::vec3(-width/2.f, -height/2.f, width/2.f);
		secondPoint = glm::vec3(-width/2.f, -height/2.f, -width/2.f);
		thirdPoint = glm::vec3(-width/2.f, height/2.f, -width/2.f);
		forthPoint = glm::vec3(-width/2.f, height/2.f, width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxLeft->unbind();
		// Right
		m_pSkyboxRight->bind();
		firstPoint = glm::vec3(width/2.f, -height/2.f, width/2.f);
		secondPoint = glm::vec3(width/2.f, -height/2.f, -width/2.f);
		thirdPoint = glm::vec3(width/2.f, height/2.f, -width/2.f);
		forthPoint = glm::vec3(width/2.f, height/2.f, width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxRight->unbind();
		// Up
		m_pSkyboxUp->bind();
		firstPoint = glm::vec3(width/2.f, height/2.f, -width/2.f);
		secondPoint = glm::vec3(-width/2.f, height/2.f, -width/2.f);
		thirdPoint = glm::vec3(-width/2.f, height/2.f, width/2.f);
		forthPoint = glm::vec3(width/2.f, height/2.f, width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxUp->unbind();
		// Down
		m_pSkyboxDown->bind();
		firstPoint = glm::vec3(width/2.f, -height/2.f, -width/2.f);
		secondPoint = glm::vec3(-width/2.f, -height/2.f, -width/2.f);
		thirdPoint = glm::vec3(-width/2.f, -height/2.f, width/2.f);
		forthPoint = glm::vec3(width/2.f, -height/2.f, width/2.f);
		LeapUtilGL::drawPolygon(LeapUtilGL::eStyle::kStyle_Solid, firstPoint/factor, secondPoint/factor, thirdPoint/factor, forthPoint/factor, 1.0);
		m_pSkyboxDown->unbind();
	}
}