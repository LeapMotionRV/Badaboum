#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <JuceHeader.h>

namespace render
{
	/**
		This component is contained in the Render. This is where we display all 2D elements.
	*/
	class Renderer2D : public juce::OpenGLTexture
	{
	public:
		Renderer2D(int width, int height);
		~Renderer2D();

		/**
		* Getters
		*/
		bool isShowHelp() const {return m_bShowHelp;}
		bool isShowDebug() const {return m_bShowDebug;}
		/**
		* Setters
		*/
		void isShowHelp(bool flag) {m_bShowHelp = flag;}
		void isShowDebug(bool flag) {m_bShowDebug = flag;}
		//updateFPS => the update of the leap motion
		void setUpdateFPS(float newUpdateFPS) {m_updateFPS = String::formatted("UpdateFPS : %4.2f", newUpdateFPS);}
		//renderFPS => the update of the rendering
		void setRenderFPS(float newRenderFPS) {m_renderFPS = String::formatted("RenderFPS : %4.2f", newRenderFPS);}
		//physicsFPS => the update of the physics
		void setPhysicsFPS(float newPhysicsFPS) {m_physicsFPS = String::formatted("PhysicsFPS : %4.2f", newPhysicsFPS);}
		void setNbParticles(unsigned int nbParticles) {m_nbParticles = String::formatted("Nb particles: %4d", nbParticles);}
		void setNbParticlesLeft(unsigned int nbParticlesLeft) {m_nbParticlesLeft = String::formatted("Nb particles left: %4d", nbParticlesLeft);}
		void setHighestPosition(float highestPosition) {m_highestPosition = String::formatted("Highest position : %4.2f", highestPosition);}
		void setGravity(float gravity) {m_gravity = String::formatted("Gravity value : %4.2f",gravity);}
		void setRigidity(float rigidity) {m_rigidity = String::formatted("Rigidity value: %4.2f",rigidity);}
		void setBrake(float brake) {m_brake = String::formatted("Brake value : %4.5f",brake);}
		void setHumanAlive(float nbHumanLeft){m_human =  String::formatted("%4.f human lives left", nbHumanLeft);}

		//draw
		void render2DDebug(OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, bool isPaused);
		void render2DHelp(OpenGLContext* pOpenGLContext);
		void render2DHome(OpenGLContext* pOpenGLContext);
		void render2DInGame(OpenGLContext* pOpenGLContext, bool isPlayerWin, bool isPlayerLoose, float nbHumanLeft, float nbHumanInitial);

	private:
		int				m_width;
		int				m_height;
		juce::Image		m_imageHome;
		juce::Image		m_imageWin;
		juce::Image		m_imageLoose;
		//the debug => for the programmer
		juce::String	m_strDebug;
		bool			m_bShowDebug;
		juce::Font		m_fixedFont;
		juce::String	m_updateFPS;
		juce::String	m_renderFPS;
		juce::String	m_physicsFPS;
		juce::String	m_nbParticles;
		juce::String	m_nbParticlesLeft;
		juce::String	m_highestPosition;
		juce::String	m_gravity;
		juce::String	m_rigidity;
		juce::String	m_brake;
		//the help => for the player
		bool			m_bShowHelp;
		juce::Image		m_imageHelp;
		//the human
		juce::String	m_human;
		float			m_humanAlpha;
		bool			up;
		bool			down;
	};
}

#endif //RENDERER2D_H