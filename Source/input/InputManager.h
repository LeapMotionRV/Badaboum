#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <JuceHeader.h>
#include "../render/Renderer.h"

namespace input
{
	/**
		Manage the "classic" inputs (mouse and keyboard).
	*/
	class InputManager : public juce::MouseListener, public juce::KeyListener
	{
	public:
		InputManager(render::Renderer* pRenderer);
		~InputManager();

		//manage inputs
		bool keyPressed(const KeyPress& keyPress, Component* originatingComponent);
		void mouseDown (const MouseEvent& e);
		void mouseDrag (const MouseEvent& e);
		void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel);

	private:
		render::Renderer*	m_pRenderer;
		/*for rotation*/
		float m_pos;
		float m_prevPos;
		float m_angle;
	};
}

#endif //INPUTMANAGER_H