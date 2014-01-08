#include "JuceHeader.h"
#include "Window.h"


class BadaboumApplication  : public JUCEApplication
{
private:
    ScopedPointer<BadaboumWindow>  m_pMainWindow; 

public:
    BadaboumApplication()
	{
	}

    ~BadaboumApplication()
    {
    }

    void initialise(const String& commandLine) 
	{
		(void) commandLine;
		m_pMainWindow = new BadaboumWindow(getApplicationName());
	}

    void shutdown()
    {
    }

    void systemRequestedQuit()
    {
        quit();
    }

    const String getApplicationName()
    {
        return "RV & MP project - Badaboum";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return false;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
      (void)commandLine;        
    }
};


// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(BadaboumApplication)
