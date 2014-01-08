#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED


#include <JuceHeader.h>
#include "Renderer.h"


/*
    This component lives inside our window, and this is where you should put all
    your controls and content (other components...).
	Usefull to display a menu before or after the openGL context (manage by an other component, in Renderer file).
*/
class MainComponent : public Component
{
private:
	static const unsigned int m_WIDTH = 1024;
	static const unsigned int m_HEIGHT = 600;

	OpenGLCanvas* m_pOpenGLRenderer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)

public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&);
    void resized();
};


#endif  // MAINCOMPONENT_H_INCLUDED
