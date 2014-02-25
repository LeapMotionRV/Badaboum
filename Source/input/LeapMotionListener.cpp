#include <windows.h>

#include "LeapMotionListener.h"
#include "../render/WindowScreen.h"
#include "../physical/forces/ConstantForce.h"

namespace input
{
	LeapMotionListener::LeapMotionListener(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
		m_isMovingCamera = false;
	}

	LeapMotionListener::~LeapMotionListener(){

	}

	void LeapMotionListener::onInit(const Leap::Controller&) {
	}

	void LeapMotionListener::onConnect(const Leap::Controller& controller) {
		//activate gestures detection
		controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
		controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
		controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
		controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
		//configure circle recognition
		if(controller.config().setFloat("Gesture.Circle.MinRadius", 10.0) && controller.config().setFloat("Gesture.Circle.MinArc", 3)){
			controller.config().save();
		}
	}

	void LeapMotionListener::onDisconnect(const Leap::Controller&) {
	}

	void LeapMotionListener::onFrame(const Leap::Controller& controller){
		if ( !m_pRenderer->isPaused() ){
			Leap::Frame frame = controller.frame();
			if(frame.isValid()){
				update(frame);
				m_pRenderer->setLastFrame(frame);
				m_pRenderer->getOpenGLContext()->triggerRepaint();
			}
		}
	}

	//
	// calculations that should only be done once per leap data frame but may be drawn many times should go here.
	//   
	void LeapMotionListener::update(Leap::Frame frame){
		//!!! lock sensitive data !!!
		juce::ScopedLock sceneLock(*m_pRenderer->getRenderMutex());

		double curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());

		float deltaTimeSeconds = static_cast<float>(curSysTimeSeconds - m_pRenderer->getLastUpdateTimeSeconds());

		m_pRenderer->setLastUpdateTimeSeconds(curSysTimeSeconds);
		float fUpdateDT = m_pRenderer->getAvgUpdateDeltaTime().AddSample( deltaTimeSeconds );
		float fUpdateFPS = (fUpdateDT > 0) ? 1.0f/fUpdateDT : 0.0f;
		m_pRenderer->getRenderer2D()->setUpdateFPS(fUpdateFPS);

		manageLeapMovements(frame);
	}

	void LeapMotionListener::manageLeapMovements(Leap::Frame frame){
		Leap::HandList hands = frame.hands();
        Leap::Hand hand = hands[0];
		bool isParticleCreated = false;
		m_isMovingCamera = false; 

		if(hand.isValid()){
			const Leap::FingerList fingers = hand.fingers();
			const Leap::GestureList gestures = frame.gestures();
		
			if(fingers.count()>=3){
					manageCamera(frame);
			}
			for (int g = 0; g < gestures.count(); ++g){
				Leap::Gesture gesture = gestures[g];
				if(fingers.count()==1 && gesture.type()==Leap::Gesture::TYPE_CIRCLE && !isParticleCreated && !m_isMovingCamera){
					createParticle(gesture);
					isParticleCreated = true;
				}
				else if(fingers.count()>=3 && gesture.type()==Leap::Gesture::TYPE_SWIPE && !m_isMovingCamera){
					triggerWind(gesture);
				}
			}
		}
	}

	void  LeapMotionListener::manageCamera(Leap::Frame &frame){

		static const float kfMinScale = 0.1f;
		static const float kfMaxScale = 2.0f;

		bool bShouldTranslate = true;
		bool bShouldRotate    = true;
		bool bShouldScale     = true;
		bShouldTranslate = frame.translationProbability(m_pRenderer->getLastFrame()) > 0.40;
		bShouldRotate    = frame.rotationProbability(m_pRenderer->getLastFrame())    > 0.40;
		bShouldScale     = frame.scaleProbability(m_pRenderer->getLastFrame())       > 0.40;

		//translation
		if(bShouldTranslate){
			m_isMovingCamera = true;
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - frame.translation(m_pRenderer->getLastFrame())/100);
		}
		else if(bShouldRotate){ //around Y axis only
			m_isMovingCamera = true;
			//get the angle of rotation around y axis
			float angleAroundY = frame.rotationAngle(m_pRenderer->getLastFrame(), Leap::Vector::yAxis());
			//compute the rotation matrix which moved an object of angleAroundY around y axis
			Leap::Matrix rotationMatrixAroundY = Leap::Matrix(
				Leap::Vector(glm::cos(angleAroundY), 0, -glm::sin(angleAroundY)), 
				Leap::Vector(0, 1, 0), 
				Leap::Vector(glm::sin(angleAroundY), 0, glm::cos(angleAroundY)));

			m_pRenderer->setTotalMotionRotation(rotationMatrixAroundY * m_pRenderer->getTotalMotionRotation()); // Left multiply, relative to last frame
		}
		//scale
		else if(bShouldScale){
			m_isMovingCamera = true;
			m_pRenderer->setTotalMotionScale(LeapUtil::Clamp(m_pRenderer->getTotalMotionScale() * frame.scaleFactor(m_pRenderer->getLastFrame()),
				kfMinScale,
				kfMaxScale ));
		}
	}

	void  LeapMotionListener::triggerWind(Leap::Gesture &gesture){
		Leap::SwipeGesture swipe = gesture;
		//create a constant force in direction of mouvement, like you make wind
		glm::vec3 force = glm::vec3(
									swipe.direction().x*swipe.speed()/1000,
									swipe.direction().y*swipe.speed()/1000,
									swipe.direction().z*swipe.speed()/1000
									);
		physical::ConstantForce wind = physical::ConstantForce(force);
		wind.apply(m_pRenderer->getModel()->getParticuleManager());
	}

	void  LeapMotionListener::createParticle(Leap::Gesture &gesture){
		Leap::CircleGesture circle = gesture;
		/*std::string clockwiseness;

		//find the circle orientation
		if (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4) {
			clockwiseness = "clockwise";
		} 
		else {
			clockwiseness = "counterclockwise";
		}

		// Calculate angle swept since last frame
		float sweptAngle = 0;
		if (circle.state() != Leap::Gesture::STATE_START) {
			Leap::CircleGesture previousUpdate = Leap::CircleGesture(render::BadaboumWindow::getController().frame(1).gesture(circle.id()));
			sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Leap::PI;
		}*/

		//When the movement of circle stopped and if there is just one hand
		if (circle.state() == Leap::Gesture::STATE_STOP && m_pRenderer->getModel()->getParticuleManager()->getNbParticles() < m_pRenderer->getModel()->getNbMaxParticle()){
			Leap::Vector coordParticleInLeapSpace = Leap::Vector(
																circle.center().x*m_pRenderer->getFrameScale(),
																circle.center().y*m_pRenderer->getFrameScale(),
																circle.center().z*m_pRenderer->getFrameScale()
																);
			//Rotation
			Leap::Vector coordParticle = m_pRenderer->getTotalMotionRotation().rigidInverse().transformPoint(coordParticleInLeapSpace);
			//Scale
			coordParticle = 1/m_pRenderer->getTotalMotionScale() * coordParticle;
			//Translation
			coordParticle = coordParticle - m_pRenderer->getTotalMotionTranslation();

			//Create particle
			glm::vec3 particlePosition = glm::vec3(coordParticle.x, coordParticle.y, coordParticle.z);
			m_pRenderer->getModel()->addParticleWhereLeapIs(particlePosition);
		}
	}
}