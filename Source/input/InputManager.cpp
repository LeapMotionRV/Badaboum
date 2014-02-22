#include "InputManager.h"

namespace input{
	
	InputManager::InputManager(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
		m_angle = 0;
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
				if(m_pRenderer->getModel()->getParticuleManager()->getNbParticles() < m_pRenderer->getModel()->getNbMaxParticle())
					m_pRenderer->getModel()->addRandomParticle(1);
				break;
			case 'Z': //more gravity
				m_pRenderer->getModel()->setGravity(m_pRenderer->getModel()->getConstantForceArray()[0]->getForce()-0.01f);
				break;
			case 'A': //less gravity
				m_pRenderer->getModel()->setGravity(m_pRenderer->getModel()->getConstantForceArray()[0]->getForce()+0.01f);
			case 'S': //more rigidity
				m_pRenderer->getModel()->getLinkManager()->setRigidity(m_pRenderer->getModel()->getLinkManager()->getRigidity()+0.01f);
				break;
			case 'Q': //less rigidity
				m_pRenderer->getModel()->getLinkManager()->setRigidity(m_pRenderer->getModel()->getLinkManager()->getRigidity()-0.01f);
				break;
			case 'X': //more brake
				m_pRenderer->getModel()->getLinkManager()->setBrake(m_pRenderer->getModel()->getLinkManager()->getBrake()+0.00001f);
				break;
			case 'W': //less brake
				m_pRenderer->getModel()->getLinkManager()->setBrake(m_pRenderer->getModel()->getLinkManager()->getBrake()-0.00001f);
				break;
			default:
				return false;
		}
		return true;
	}

	void InputManager::mouseDown (const MouseEvent&){
	}



	void InputManager::mouseDrag (const MouseEvent& e){
		//100 is the keyCode for letter D
		if(KeyPress::isKeyCurrentlyDown(100)){
			//multiply by 0.01 to avoid a too important rotation
			m_angle +=  e.getDistanceFromDragStartX()*0.01;
			m_pRenderer->setTotalMotionRotation(/*m_pRenderer->getTotalMotionRotation().xBasis.x*/ -e.getDistanceFromDragStartX()*0.01);
		}
	}

	void InputManager::mouseWheelMove ( const MouseEvent& e, const MouseWheelDetails& wheel ){
		(void)e;
		m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + Leap::Vector(0, 0, wheel.deltaY));
		m_pRenderer->getOpenGLContext()->triggerRepaint();
	}
}