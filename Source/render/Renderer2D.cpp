#include "../util/LeapUtilGL.h"
#include "Renderer2D.h"

namespace render
{
	Renderer2D::Renderer2D(int width, int height){
		m_width = width;
		m_height = height;

		//the font
		m_fixedFont = Font("Courier New", 24, Font::plain );

		//the help
		m_bShowHelp = false;
		m_strHelp = "ESC   - quit\n"
					"h     - Toggle help and frame rate display\n"
					"Space - Toggle pause\n"
					"r     - Reset camera\n"
					"\n"
					"Mouse Wheel - Zoom camera\n"
					"Arrow Keys  - Translate camera\n"
					"d + left click & drag  - rotation\n"
					"\n"
					"p    - Create a random particle\n"
					"z/a  - In/Decrease gravity\n"
					"q/s  - In/Decrease rigidity\n"
					"w/x  - In/Decrease brake\n";
		m_strPrompt = "Press 'h' for help";

		//data
		m_updateFPS = juce::String();
		m_renderFPS = juce::String();
		m_nbParticles = juce::String();
		m_highestPosition = juce::String();
	}

	Renderer2D::~Renderer2D(){
	}

	void Renderer2D::renderOpenGL2D(juce::OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, bool isPaused) {
		LeapUtilGL::GLAttribScope attribScope(GL_ENABLE_BIT);

		// when enabled text draws poorly.
		glDisable(GL_CULL_FACE);

		juce::ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (*pOpenGLContext, m_width, m_height));

		if (glRenderer != nullptr){
			juce::Graphics g(*glRenderer.get());

			int iMargin   = 10;
			int iFontSize = static_cast<int>(m_fixedFont.getHeight());
			int iLineStep = iFontSize + (iFontSize >> 2);
			int iBaseLine = 20;
			Font origFont = g.getCurrentFont();

			if ( m_bShowHelp ){
				g.setColour(juce::Colours::seagreen);
				g.setFont( static_cast<float>(iFontSize) );

				if ( !isPaused ){
					g.drawSingleLineText(m_updateFPS, iMargin, iBaseLine);
				}
				g.drawSingleLineText(m_renderFPS, iMargin, iBaseLine + iLineStep);
				g.drawSingleLineText(m_nbParticles, iMargin, iBaseLine + iLineStep*2);
				g.drawSingleLineText(m_nbParticlesLeft, iMargin, iBaseLine + iLineStep*3);
				g.drawSingleLineText(m_highestPosition, iMargin, iBaseLine + iLineStep*4);
				g.drawSingleLineText(m_gravity, iMargin, iBaseLine + iLineStep*5);
				g.drawSingleLineText(m_rigidity, iMargin, iBaseLine + iLineStep*6);
				g.drawSingleLineText(m_brake, iMargin, iBaseLine + iLineStep*7);

				g.setFont( m_fixedFont );
				g.setColour( Colours::slateblue );

				g.drawMultiLineText(  m_strHelp,
										iMargin,
										iBaseLine + iLineStep * 9,
										bouds.getWidth() - iMargin*2 );
			}

			g.setFont( origFont );
			g.setFont( static_cast<float>(iFontSize) );

			g.setColour( Colours::salmon );
			g.drawMultiLineText(  m_strPrompt,
									iMargin,
									bouds.getBottom() - (iFontSize + iFontSize + iLineStep) + 75,
									bouds.getWidth()/4 );
		}
	}
}