#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <JuceHeader.h>

namespace render
{
	/**
		This component is contained in the Render. This is where we display all 2D elements.
	*/
	class Renderer2D
	{
	public:
		Renderer2D(int width, int height);
		~Renderer2D();

		/**
		* Getters
		*/
		bool isShowHelp() const {return m_bShowHelp;}
		/**
		* Setters
		*/
		void isShowHelp(bool flag) {m_bShowHelp = flag;}
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
		void setHumanAlive(unsigned int nbParticles, int time){
			if(m_previousParticleNb!=nbParticles){
				++m_previousParticleNb;
				m_humanNumber -= 100000000 + time;
			}
			else
				m_humanNumber -= time;
			m_human =  String::formatted("%4.f human lives left", m_humanNumber);
		}

		//draw the text overlay (the help)
		void renderOpenGL2D(OpenGLContext* pOpenGLContext, const juce::Rectangle<int>& bouds, bool isPaused);

	private:
		//to have the good size to display
		int				m_width;
		int				m_height;
		float			m_humanNumber;
		unsigned int	m_previousParticleNb;
		//the font
		juce::Font		m_fixedFont;
		//the help
		juce::String	m_strPrompt;
		juce::String	m_strHelp;
		bool			m_bShowHelp;
		//data
		juce::String	m_updateFPS;
		juce::String	m_renderFPS;
		juce::String	m_physicsFPS;
		juce::String	m_nbParticles;
		juce::String	m_nbParticlesLeft;
		juce::String	m_highestPosition;
		juce::String	m_gravity;
		juce::String	m_rigidity;
		juce::String	m_brake;
		juce::String	m_human;

		//juce::DrawableRectangle* m_background;
	};
}

#endif //RENDERER2D_H