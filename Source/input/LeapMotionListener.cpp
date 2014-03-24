#include <windows.h>

#include "LeapMotionListener.h"
#include "../render/WindowScreen.h"
#include "../physical/forces/ConstantForce.h"

namespace input
{
	LeapMotionListener::LeapMotionListener(render::Renderer* pRenderer){
		m_pRenderer = pRenderer;
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
		// Gesture.Circle.MinRadius | float | default value = 5.0 | mm
        // Gesture.Circle.MinArc | float | default value = 1.5*pi | radians
		if(controller.config().setFloat("Gesture.Circle.MinRadius", 20.0) 
			&& controller.config().setFloat("Gesture.Circle.MinArc", 2*Leap::PI)){
			controller.config().save();
		}
		// configure swipe recognition
		// Gesture.Swipe.MinLength | float | default value = 150 | mm
        // Gesture.Swipe.MinVelocity | float | default value = 1000 | mm/s
		if(controller.config().setFloat("Gesture.Swipe.MinLength", 150) 
			&& controller.config().setFloat("Gesture.Swipe.MinVelocity", 100)){
			controller.config().save();
		}
	}

	void LeapMotionListener::onDisconnect(const Leap::Controller&) {
	}

	void LeapMotionListener::onFrame(const Leap::Controller& controller){
		if ( !m_pRenderer->isPaused() && !m_pRenderer->getRenderer2D()->isShowHelp()){
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
		m_pRenderer->setLastUpdateTimeSeconds(curSysTimeSeconds);

		manageLeapMovements(frame);
	}

	void LeapMotionListener::manageLeapMovements(Leap::Frame frame){
		Leap::HandList hands = frame.hands();
		Leap::FingerList fingers = frame.fingers();
		for(size_t i = 0; i < hands.count(); ++i){
			if(!hands[i].isValid())
				return;
		}

		const Leap::FingerList fingersHand0 = hands[0].fingers();
		const Leap::GestureList gestures = frame.gestures();
		if(hands.count() == 2 && fingers.count() > 5){
			manageCamera(frame);
		}
		else{
			//manage each gesture
			for (int g = 0; g < gestures.count(); ++g){
				Leap::Gesture gesture = gestures[g];
				//create particle
				if(fingersHand0.count() == 1 && gesture.type() == Leap::Gesture::TYPE_CIRCLE){
					if(m_pRenderer->getModel()->getParticuleManager()->getNbParticles() < m_pRenderer->getModel()->getNbMaxParticle()){
						if(gesture.state() == Leap::Gesture::STATE_STOP)
							createParticle(gesture);
					}
				}
				//trigger wind
				else if(fingersHand0.count() >= 3 && gesture.type() == Leap::Gesture::TYPE_SWIPE){
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
			m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - frame.translation(m_pRenderer->getLastFrame())/100);
		}
		//rotation around Y axis only
		else if(bShouldRotate){
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
		//the getFrameScale allows to come back to the good position in our space
		Leap::Vector coordParticle = Leap::Vector(
															circle.center().x*m_pRenderer->getFrameScale(),
															circle.center().y*m_pRenderer->getFrameScale(),
															circle.center().z*m_pRenderer->getFrameScale()
															);

		//Normally, we should just do tranformations during the drawing, but there is a little trick here because our hands, which
		//create the particles, are not subjected to the same transformations than the scene and we have to create the particle at the good point !
		//so we  do the inverse transformations of which made on the scene to came back to the basic repair of hands
		
		//Translation
		coordParticle = coordParticle - m_pRenderer->getTotalMotionTranslation();
		//Rotation
		coordParticle = m_pRenderer->getTotalMotionRotation().rigidInverse().transformPoint(coordParticle);
		//Scale
		coordParticle = 1/m_pRenderer->getTotalMotionScale() * coordParticle;



		//Create particle
		glm::vec3 particlePosition = glm::vec3(coordParticle.x, coordParticle.y, coordParticle.z);
		m_pRenderer->getModel()->addParticleWhereLeapIs(particlePosition);
	}
}