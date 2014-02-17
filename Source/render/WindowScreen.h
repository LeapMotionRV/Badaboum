#ifndef WINDOW_H
#define WINDOW_H


#include <JuceHeader.h>
#include "Renderer.h"
#include "MainComponent.h"


namespace render
{
	/**
		A resizable window with a title bar and maximise, minimise and close buttons.
		This class contains the Leap's Controller.
	*/
	class BadaboumWindow : public DocumentWindow
	{
	private:
		MainComponent* m_pMainComponent;
	public:
		//return the controller (singleton)
		static Leap::Controller& getController() 
		{
			static Leap::Controller s_controller;
			return  s_controller;
		}

		BadaboumWindow(String applicationName);
		~BadaboumWindow();

		void closeButtonPressed();
	};
}

#endif //WINDOW_H