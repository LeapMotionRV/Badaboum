#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <JuceHeader.h>

namespace render
{
	/**
		Contain and render all 2D elements.
	*/
	class Renderer2D
	{
	public:
		Renderer2D(int width, int height);
		~Renderer2D();

		//getters
		bool isShowHelp() const {return m_bShowHelp;}

		//setters
		void isShowHelp(bool flag) {m_bShowHelp = flag;}
		void setUpdateFPS(float newUpdateFPS) {m_updateFPS = String::formatted("UpdateFPS : %4.2f", newUpdateFPS);}
		void setRenderFPS(float newRenderFPS) {m_renderFPS = String::formatted("RenderFPS : %4.2f", newRenderFPS);}
		void setNbParticles(size_t nbParticles) {m_nbParticles = String::formatted("Nb particles: %4.i", nbParticles);}
		void setHighestPosition(float highestPosition) {m_highestPosition = String::formatted("Highest position : %4.2f", highestPosition);}

		//draw the text overlay (the help)
		void renderOpenGL2D(OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, bool isPaused);

	private:
		//to have the good size to display
		int				m_width;
		int				m_height;
		//the font
		juce::Font		m_fixedFont;
		//the help
		juce::String	m_strPrompt;
		juce::String	m_strHelp;
		bool			m_bShowHelp;
		//data
		juce::String	m_updateFPS;
		juce::String	m_renderFPS;
		juce::String	m_nbParticles;
		juce::String	m_highestPosition;
	};
}

#endif //RENDERER2D_H