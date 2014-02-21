#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED


#include <JuceHeader.h>

#include "../physical/Model.h"
#include "Renderer.h"
#include "../input/InputManager.h"
#include "../input/LeapMotionListener.h"


namespace render
{
	/*
		This component lives inside our window, and this is where you should put all
		your controls and content (other components...).
		Usefull to display a menu before or after the openGL context (manage by an other component, in Renderer file).
	*/
	class MainComponent : public Component
	{
	public:
		MainComponent();
		~MainComponent();

		void paint (Graphics&);
		void resized();
	
	private:
		static const unsigned int	m_WIDTH = 1024;
		static const unsigned int	m_HEIGHT = 600;

		physical::Model*			m_pModel;
		Renderer*					m_pOpenGLRenderer;
		input::InputManager*		m_pInputManager;
		input::LeapMotionListener*	m_pLeapMotionListener;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
	};
}

#endif  // MAINCOMPONENT_H_INCLUDED