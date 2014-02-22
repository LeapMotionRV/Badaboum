#include "InputManager.h"

namespace input{
	
	InputManager::InputManager(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
	}

	InputManager::~InputManager(){

	}

	bool InputManager::keyPressed(const KeyPress& keyPress, Component*)  {
		int iKeyCode = toupper(keyPress.getKeyCode());

		//ECHAP
		if ( iKeyCode == KeyPress::escapeKey ){
			JUCEApplication::quit();
			return true;
		}
		//UP
		if ( iKeyCode == KeyPress::upKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - Leap::Vector(0, 1, 0));
			return true;
		}
		//DOWN
		if ( iKeyCode == KeyPress::downKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + Leap::Vector(0, 1, 0));
			return true;
		}
		//LEFT
		if ( iKeyCode == KeyPress::leftKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + Leap::Vector(1, 0, 0));
			return true;
		}
		//RIGHT
		if ( iKeyCode == KeyPress::rightKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - Leap::Vector(1, 0, 0));
			return true;
		}
		//ESCAPE
		if ( iKeyCode == KeyPress::escapeKey ){
			m_pRenderer->isPaused(!m_pRenderer->isPaused());
			return true;
		}
		//Caracters
		switch( iKeyCode ){
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

	void InputManager::mouseDown (const MouseEvent&){
	}

	void InputManager::mouseDrag (const MouseEvent&){
	}

	void InputManager::mouseWheelMove ( const MouseEvent& e, const MouseWheelDetails& wheel ){
		(void)e;
		m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + Leap::Vector(0, 0, wheel.deltaY));
		m_pRenderer->getOpenGLContext()->triggerRepaint();
	}
}