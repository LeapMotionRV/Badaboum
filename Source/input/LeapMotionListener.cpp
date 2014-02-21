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

	void LeapMotionListener::onInit(const Leap::Controller&) 
	{
	}

	void LeapMotionListener::onConnect(const Leap::Controller& controller) 
	{
		//activate gestures detection
		controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
		controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
		controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
		controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
		//configure circle recognition
		if(controller.config().setFloat("Gesture.Circle.MinRadius", 20.0) && controller.config().setFloat("Gesture.Circle.MinArc", 3)){
			controller.config().save();
		}
	}

	void LeapMotionListener::onDisconnect(const Leap::Controller&) 
	{
	}

	void LeapMotionListener::onFrame(const Leap::Controller& controller)
	{
		if ( !m_pRenderer->isPaused() )
		{
			Leap::Frame frame = controller.frame();
			if(frame.isValid()){
				update(frame);
				m_pRenderer->setLastFrame(frame);
				m_pRenderer->getCurrentOpenGLContext()->triggerRepaint();
			}
		}
	}

	//
	// calculations that should only be done once per leap data frame but may be drawn many times should go here.
	//   
	void LeapMotionListener::update(Leap::Frame frame)
	{
		ScopedLock sceneLock(*m_pRenderer->getRenderMutex());

		double curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());

		float deltaTimeSeconds = static_cast<float>(curSysTimeSeconds - m_pRenderer->getLastUpdateTimeSeconds());
      
		m_pRenderer->setLastUpdateTimeSeconds(curSysTimeSeconds);
		float fUpdateDT = m_pRenderer->getAvgUpdateDeltaTime().AddSample( deltaTimeSeconds );
		float fUpdateFPS = (fUpdateDT > 0) ? 1.0f/fUpdateDT : 0.0f;
		m_pRenderer->getRenderer2D()->setUpdateFPS(fUpdateFPS);

		manageLeapMovements(frame);
	}

	void LeapMotionListener::manageLeapMovements(Leap::Frame frame){
		// ******************** //
		//    Manage camera     //
		// ******************** //
		bool isMoving = false;

		static const float kfMinScale = 0.1f;
        static const float kfMaxScale = 2.0f;

		bool bShouldTranslate = true;
        bool bShouldRotate    = true;
        bool bShouldScale     = true;
		bShouldTranslate = frame.translationProbability(m_pRenderer->getLastFrame()) > 0.40;
        bShouldRotate    = frame.rotationProbability(m_pRenderer->getLastFrame())    > 0.40;
        bShouldScale     = frame.scaleProbability(m_pRenderer->getLastFrame())       > 0.40;

		//if any hands
		if (!frame.hands().isEmpty()) 
		{
			// Get the first hand
			const Leap::Hand hand = frame.hands()[0];

			// Check if the hand has any fingers
			const Leap::FingerList fingers = hand.fingers();
			if (!fingers.isEmpty()) 
			{
				Leap::Vector avgPos;
				// Calculate the hand's average finger tip position
				for (int i = 0; i < fingers.count(); ++i) 
				{
					avgPos += fingers[i].tipPosition();
				}
				avgPos /= (float)fingers.count();
			}

			// Get the hand's sphere radius and palm position
			std::cout << "Hand sphere radius: " << hand.sphereRadius()
						<< " mm, palm position: " << hand.palmPosition() << std::endl;

			// Get the hand's normal vector and direction
			const Leap::Vector normal = hand.palmNormal();
			const Leap::Vector direction = hand.direction();
			
			//Move the camera with the leap motion
			int number = (int)fingers.count();
			if(number > 4){
				isMoving = true;
				if(bShouldTranslate)
					m_pRenderer->setTotalMotionTranslation(m_pRenderer->getTotalMotionTranslation() - m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(frame.translation(m_pRenderer->getLastFrame())/100));
				else if(bShouldRotate){
					m_pRenderer->setTotalMotionRotation(frame.rotationMatrix(m_pRenderer->getLastFrame()) * m_pRenderer->getTotalMotionRotation()); // Left multiply, relative to last frame
				}
				else if(bShouldScale)
					m_pRenderer->setTotalMotionScale(LeapUtil::Clamp(m_pRenderer->getTotalMotionScale() * frame.scaleFactor(m_pRenderer->getLastFrame()),
														  kfMinScale,
														  kfMaxScale ));
			}

			// Calculate the hand's pitch, roll, and yaw angles
			std::cout << "Hand pitch: " << direction.pitch() * Leap::RAD_TO_DEG << " degrees, "
						<< "roll: " << normal.roll() * Leap::RAD_TO_DEG << " degrees, "
						<< "yaw: " << direction.yaw() * Leap::RAD_TO_DEG << " degrees" << std::endl;
		}

		if(!isMoving){
			// Get gestures
			const Leap::GestureList gestures = frame.gestures();
			for (int g = 0; g < gestures.count(); ++g)
			{
				Leap::Gesture gesture = gestures[g];

				switch (gesture.type()) 
				{
					case Leap::Gesture::TYPE_CIRCLE:
					{
						Leap::CircleGesture circle = gesture;
						OutputDebugString("CircleGesture");
						std::string clockwiseness;

						//find the circle orientation
						if (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4) 
						{
							clockwiseness = "clockwise";
						} 
						else 
						{
							clockwiseness = "counterclockwise";
						}

						// Calculate angle swept since last frame
						float sweptAngle = 0;
						if (circle.state() != Leap::Gesture::STATE_START) 
						{
							Leap::CircleGesture previousUpdate = Leap::CircleGesture(render::BadaboumWindow::getController().frame(1).gesture(circle.id()));
							sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Leap::PI;
						}

						//if just one hand
						if(frame.hands().count() == 1){
							if(frame.hands()[0].fingers().count() <= 5){
								//When the movement of circle stopped
								if (circle.state() == Leap::Gesture::STATE_STOP)
								{
									OutputDebugString("circle completed");
									Leap::Vector coordLeapToWorld = Leap::Vector(circle.center().x*m_pRenderer->getFrameScale(), circle.center().y*m_pRenderer->getFrameScale(), circle.center().z*m_pRenderer->getFrameScale());
									coordLeapToWorld = coordLeapToWorld*(1/m_pRenderer->getTotalMotionScale());//scale the translation according to the world
									Leap::Vector coordLeapToWorldRotated = m_pRenderer->getTotalMotionRotation().rigidInverse().transformDirection(coordLeapToWorld);
									glm::vec3 particlePosition = glm::vec3(
										coordLeapToWorldRotated.x-((1/m_pRenderer->getTotalMotionScale())*m_pRenderer->getTotalMotionTranslation().x), 
										coordLeapToWorldRotated.y-((1/m_pRenderer->getTotalMotionScale())*m_pRenderer->getTotalMotionTranslation().y), 
										coordLeapToWorldRotated.z-((1/m_pRenderer->getTotalMotionScale())*m_pRenderer->getTotalMotionTranslation().z));
									m_pRenderer->getModel()->addParticleWhereLeapIs(glm::vec3(coordLeapToWorld.x, coordLeapToWorld.y, coordLeapToWorld.z));
								}

								break;
							}
						}
					}
					case Leap::Gesture::TYPE_SWIPE:
					{
						Leap::SwipeGesture swipe = gesture;
						OutputDebugString("SwipeGesture");

						//create a constant force in direction of mouvement, like you make wind
						glm::vec3 force = glm::vec3(swipe.direction().x * swipe.speed()/1000, swipe.direction().y*swipe.speed()/1000, swipe.direction().z*swipe.speed()/1000);
						physical::ConstantForce wind = physical::ConstantForce(force);
						wind.apply(m_pRenderer->getModel()->getParticuleManager());

						break;
					}
					case Leap::Gesture::TYPE_KEY_TAP:
					{
						OutputDebugString("KeyTapGesture");
						break;
					}
					case Leap::Gesture::TYPE_SCREEN_TAP:
					{
						OutputDebugString("ScreenTapGesture");
						break;
					}
					default:
						OutputDebugString("Unknown gesture type\n");
						break;
				}
			}
		}
	}
}