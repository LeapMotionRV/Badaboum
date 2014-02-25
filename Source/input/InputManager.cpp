#include "InputManager.h"
#include "Windows.h"
namespace input{
	
	InputManager::InputManager(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
		m_pos = 0;
		m_prevPos = 0;
		m_angle = 0.f;
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
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(Leap::Vector(0, 1, 0)));
			return true;
		}
		//DOWN
		if ( iKeyCode == KeyPress::downKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(Leap::Vector(0, 1, 0)));
			return true;
		}
		//LEFT
		if ( iKeyCode == KeyPress::leftKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(Leap::Vector(1, 0, 0)));
			return true;
		}
		//RIGHT
		if ( iKeyCode == KeyPress::rightKey ){
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(Leap::Vector(1, 0, 0)));
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
				m_prevPos = m_pos;
				m_pos = 0;
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

	void InputManager::mouseDown (const MouseEvent& e){
		m_prevPos = e.getMouseDownScreenX();
		m_pos = e.getMouseDownScreenX();
	}



	void InputManager::mouseDrag (const MouseEvent& e){
		//100 is the keyCode for letter D
		if(KeyPress::isKeyCurrentlyDown(100)){
			m_pos = e.getScreenX();
			if(m_pos<m_prevPos) m_angle=-0.05f;
			else m_angle=0.05f;
			Leap::Matrix rotationMatrix = Leap::Matrix(Leap::Vector(glm::cos(m_angle), 0, -glm::sin(m_angle)), 
													   Leap::Vector(0, 1, 0), 
													   Leap::Vector(glm::sin(m_angle), 0, glm::cos(m_angle)));
			m_pRenderer->setTotalMotionRotation(rotationMatrix * m_pRenderer->getTotalMotionRotation()); 
			m_prevPos = m_pos;
		}
	}

	void InputManager::mouseWheelMove ( const MouseEvent& e, const MouseWheelDetails& wheel ){
		(void)e;
		m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() + m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(Leap::Vector(0, 0, wheel.deltaY)));
		m_pRenderer->getOpenGLContext()->triggerRepaint();
	}
}