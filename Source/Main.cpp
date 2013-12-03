#include "JuceHeader.h"
#include "Window.h"


class FingerVisualizerApplication  : public JUCEApplication
{
private:
    ScopedPointer<FingerVisualizerWindow>  m_pMainWindow; 

public:
    FingerVisualizerApplication()
    {
    }

    ~FingerVisualizerApplication()
    {
    }

    void initialise (const String& commandLine) 
	{
		(void) commandLine;
		m_pMainWindow = new FingerVisualizerWindow();
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
        return "RV project - Badaboum";
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
START_JUCE_APPLICATION(FingerVisualizerApplication)
