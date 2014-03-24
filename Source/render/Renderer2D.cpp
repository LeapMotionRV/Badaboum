#include "../util/LeapUtilGL.h"
#include "Renderer2D.h"

namespace render
{
	Renderer2D::Renderer2D(int width, int height){
		m_width = width;
		m_height = height;
		//the font
		m_fixedFont = Font("Courier New", 24, Font::plain );
		m_humanAlpha = 1.0;

		//the debug
		m_bShowDebug = false;
		m_strDebug = "ESC   - quit\n"
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

		//the help
		m_bShowHelp = false;
		//create texture for the help
		juce::File fileHelp = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/ApocaLeap.jpg");
		if(!fileHelp.existsAsFile()){
			std::cout << "Error when loading texture of the help." << std::endl;
		}
		else {
			m_imageHelp = juce::ImageCache::getFromFile(fileHelp);
		}
		//data
		//m_human =  String::formatted("%4.f human lives left", m_humanNumber);
		//m_background = new DrawableRectangle();
		//m_background->setRectangle(RelativeParallelogram(RelativePoint(0.0, 0.0), RelativePoint(5.0, 0.0), RelativePoint(0.0, 3.0)));
	}

	Renderer2D::~Renderer2D(){
	}

	void Renderer2D::render2DDebug(juce::OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, bool isPaused) {
		LeapUtilGL::GLAttribScope attribScope(GL_ENABLE_BIT);

		// when enabled text draws poorly.
		glDisable(GL_CULL_FACE);

		juce::ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (*pOpenGLContext, m_width, m_height));

		if (glRenderer != nullptr && m_bShowDebug){
			juce::Graphics g(*glRenderer.get());

			int iMargin   = 10;
			int iFontSize = static_cast<int>(m_fixedFont.getHeight());
			int iLineStep = iFontSize + (iFontSize >> 2);
			int iBaseLine = 20;
			Font origFont = g.getCurrentFont();

			g.setColour(juce::Colours::seagreen);
			g.setFont( static_cast<float>(iFontSize) );

			if ( !isPaused ){
				g.drawSingleLineText(m_updateFPS, iMargin, iBaseLine);
			}
			g.drawSingleLineText(m_renderFPS, iMargin, iBaseLine + iLineStep);
			g.drawSingleLineText(m_physicsFPS, iMargin, iBaseLine + iLineStep*2);
			g.drawSingleLineText(m_nbParticles, iMargin, iBaseLine + iLineStep*3);
			g.drawSingleLineText(m_nbParticlesLeft, iMargin, iBaseLine + iLineStep*4);
			g.drawSingleLineText(m_highestPosition, iMargin, iBaseLine + iLineStep*5);
			g.drawSingleLineText(m_gravity, iMargin, iBaseLine + iLineStep*6);
			g.drawSingleLineText(m_rigidity, iMargin, iBaseLine + iLineStep*7);
			g.drawSingleLineText(m_brake, iMargin, iBaseLine + iLineStep*8);

			//g.drawRect(m_background);
			g.drawSingleLineText(m_human, m_width, iBaseLine + iLineStep);

			g.setFont( m_fixedFont );
			g.setColour( Colours::slateblue );

			g.drawMultiLineText(  m_strDebug,
									iMargin,
									iBaseLine + iLineStep * 9,
									bouds.getWidth() - iMargin*2 );
		}
	}

	void Renderer2D::render2DHelp(juce::OpenGLContext* pOpenGLContext) {
		LeapUtilGL::GLAttribScope attribScope(GL_ENABLE_BIT);

		// when enabled text draws poorly.
		glDisable(GL_CULL_FACE);

		juce::ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (*pOpenGLContext, m_width, m_height));

		if (glRenderer != nullptr){
			juce::Graphics g(*glRenderer.get());
			g.drawImage(m_imageHelp, 0, 0, m_width, m_height, 0, 0, m_imageHelp.getWidth(), m_imageHelp.getHeight());
		}
	}

	void Renderer2D::render2DInGame(juce::OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, float nbHumanLeft, float nbHumanInitial) {
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

			g.setFont( static_cast<float>(iFontSize) );

			g.setColour( Colours::black);
			g.fillRect(5, 5, 300, 25);
			g.setOpacity(0.5);

			if(nbHumanLeft<nbHumanInitial*0.5){
				g.setColour( Colours::red);
				//m_humanAlpha
			}
			else if(nbHumanLeft<nbHumanInitial*0.75){
				g.setColour( Colours::orange);
			}
			else{
				g.setColour(juce::Colours::green);
			}
			g.setOpacity(1.0);
			g.drawSingleLineText(m_human, 10, 25);

		}
	}
}