#include "InputManager.h"

namespace input{
	
	InputManager::InputManager(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
	}

	InputManager::~InputManager(){

	}

	bool InputManager::keyPressed(const KeyPress& keyPress, Component* ) //originatingComponent
	{
		int iKeyCode = toupper(keyPress.getKeyCode());

		//ECHAP
		if ( iKeyCode == KeyPress::escapeKey )
		{
			JUCEApplication::quit();
			return true;
		}
		//UP
		if ( iKeyCode == KeyPress::upKey )
		{
			//m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * -0.05f );
			//m_camera.Move(Leap::Vector(0.f, 0.2f, 0.f));
			return true;
		}
		//DOWN
		if ( iKeyCode == KeyPress::downKey )
		{
			//m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * 0.05f );
			//m_camera.Move(Leap::Vector(0.f, -0.2f, 0.f));
			return true;
		}
		//LEFT
		if ( iKeyCode == KeyPress::leftKey )
		{
			//m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * -0.05f, 0 );
			//m_camera.Move(Leap::Vector(-0.2f, 0.f, 0.f));
			return true;
		}
		//RIGHT
		if ( iKeyCode == KeyPress::rightKey )
		{
			//m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * 0.05f, 0 );
			//m_camera.Move(Leap::Vector(0.2f, 0.f, 0.f));
			return true;
		}
		//ESCAPE
		if ( iKeyCode == KeyPress::escapeKey )
		{
			m_pRenderer->isPaused(!m_pRenderer->isPaused());
			return true;
		}
		//Caracters
		switch( iKeyCode )
		{
			case ' ':
				m_pRenderer->isPaused(!m_pRenderer->isPaused());
				break;
			case 'R':
				m_pRenderer->resetCamera();
				m_pRenderer->resetScene();
				break;
			case 'H':
				m_pRenderer->getRenderer2D()->isShowHelp(!m_pRenderer->getRenderer2D()->isShowHelp());
				break;
			case 'P': //add a particle
				m_pRenderer->getModel()->addRandomParticle(1);
				break;
			default:
				return false;
		}

		return true;
	}

	void InputManager::mouseDown (const MouseEvent& e)
	{
		//m_camera.OnMouseDown( LeapUtil::FromVector2( e.getPosition() ) );
	}

	void InputManager::mouseDrag (const MouseEvent& e)
	{
		//m_camera.OnMouseMoveOrbit( LeapUtil::FromVector2( e.getPosition() ) );
		m_pRenderer->getOpenGLContext()->triggerRepaint();
	}

	void InputManager::mouseWheelMove ( const MouseEvent& e, const MouseWheelDetails& wheel )
	{
		(void)e;
		//m_camera.OnMouseWheel( wheel.deltaY );
		m_pRenderer->getOpenGLContext()->triggerRepaint();
	}
}