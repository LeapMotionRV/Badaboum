#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include <Leap.h>

#include "../render/Renderer.h"
#include "../sound/SoundManager.h"

namespace input
{
	/**
		Manage the Leap Motion.
	*/
	class LeapMotionListener : public Leap::Listener
	{
	public:
		LeapMotionListener(render::Renderer* pRenderer, sound::SoundManager* pSoundManager);
		~LeapMotionListener();

		void update(Leap::Frame frame);
		void manageLeapMovements(Leap::Frame frame);
		void manageCamera(Leap::Frame &frame);
		void triggerWind(Leap::Gesture &gesture);
		void createParticle(Leap::Gesture &gesture);

		void triggerGameBySwipe();

		//functions from the Listener
		virtual void onInit(const Leap::Controller&);
		virtual void onConnect(const Leap::Controller&);
		virtual void onDisconnect(const Leap::Controller&);
		virtual void onFrame(const Leap::Controller& controller);

	private:
		render::Renderer*		m_pRenderer;
		sound::SoundManager*	m_pSoundManager;
	};
}

#endif //LEAPMOTIONLISTENER_H