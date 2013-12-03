#include "Window.h"


BadaboumWindow::BadaboumWindow()
	:DocumentWindow("Leap Finger Visualizer",
					Colours::darkcyan,
					DocumentWindow::allButtons,
					true) 
{
	m_pMainComponent = new MainComponent();
	setContentOwned(m_pMainComponent, true);
        
	// Centre the window on the screen
    centreWithSize(getWidth(), getHeight());

    // And show it!
    setVisible(true);

    getChildComponent(0)->grabKeyboardFocus();
}

BadaboumWindow::~BadaboumWindow()
{
    delete m_pMainComponent;
}

void BadaboumWindow::closeButtonPressed()
{
    JUCEApplication::quit();
}