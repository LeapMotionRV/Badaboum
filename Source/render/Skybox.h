#ifndef SKYBOX_H
#define SKYBOX_H


#include <JuceHeader.h>
#include "..\util\LeapUtilGL.h"

namespace render
{
	class Skybox
	{
	public:
		Skybox();
		~Skybox();

		void createTexture();
		void draw(Leap::Vector totalTranslation, float totalScale);
		void draw(Leap::Matrix rotationMatrix, Leap::Vector totalTranslation, float totalScale);

	private:
		juce::OpenGLTexture* m_pSkyboxUp;
		juce::OpenGLTexture* m_pSkyboxDown;
		juce::OpenGLTexture* m_pSkyboxLeft;
		juce::OpenGLTexture* m_pSkyboxRight;
		juce::OpenGLTexture* m_pSkyboxForward;
		juce::OpenGLTexture* m_pSkyboxBack;
	};
}

#endif