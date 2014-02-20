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
		void setUpdateFPS(juce::String newUpdateFPS) {m_updateFPS = newUpdateFPS;}
		void setRenderFPS(juce::String newRenderFPS) {m_renderFPS = newRenderFPS;}
		void setNbParticles(size_t nbParticles) {m_nbParticles = String::formatted( "nb particles: %4.i", nbParticles );}

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
	};
}

#endif //RENDERER2D_H