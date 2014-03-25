#include "WindowScreen.h"

namespace render
{
	BadaboumWindow::BadaboumWindow(String applicationName)
		:DocumentWindow(applicationName,
						Colours::darkcyan,
						DocumentWindow::closeButton,
						true) 
	{
		m_pMainComponent = new MainComponent();
		setContentOwned(m_pMainComponent, true);
    
		// Set an icon
		juce::File fileIco = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/icon.ico");
		if(!fileIco.existsAsFile()){
			std::cout << "Error when loading texture of the ico." << std::endl;
		}
		else {
			setIcon(juce::ImageCache::getFromFile(fileIco));
		}

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
}