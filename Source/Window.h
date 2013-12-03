#ifndef WINDOW_H
#define WINDOW_H


#include "JuceHeader.h"
#include "Renderer.h"


/**
	A resizable window with a title bar and maximise, minimise and close buttons.
*/
class FingerVisualizerWindow : public DocumentWindow
{
private:
	SampleListener* listener;
	OpenGLCanvas* m_pOpenGLEnvironment;
public:
    FingerVisualizerWindow():DocumentWindow("Leap Finger Visualizer",
											Colours::darkcyan,
											DocumentWindow::allButtons,
											true) 
	{
		m_pOpenGLEnvironment = new OpenGLCanvas();
		setContentOwned (m_pOpenGLEnvironment, true);
        
		// Centre the window on the screen
        centreWithSize (getWidth(), getHeight());

        // And show it!
        setVisible (true);

        getChildComponent(0)->grabKeyboardFocus();
    }

    ~FingerVisualizerWindow()
    {
        delete m_pOpenGLEnvironment;
    }

    void closeButtonPressed()
    {
        JUCEApplication::quit();
    }
};

#endif //WINDOW_H