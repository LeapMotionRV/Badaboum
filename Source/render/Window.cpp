#include "Window.h"


BadaboumWindow::BadaboumWindow(String applicationName)
	:DocumentWindow(applicationName,
					Colours::darkcyan,
					DocumentWindow::closeButton,
					true) 
{
	m_pMainComponent = new MainComponent();
	setContentOwned(m_pMainComponent, true);
    
	// Set an icon
	//void 	setIcon (const Image &imageToUse)

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