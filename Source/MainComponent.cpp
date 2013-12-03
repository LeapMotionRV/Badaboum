#include "MainComponent.h"

MainComponent::MainComponent()
{
    //setSize (1024, 600); //don't know the differences with setBounds...
    setBounds(0, 0, m_WIDTH, m_HEIGHT);//768

	m_pOpenGLRenderer = new OpenGLCanvas(m_WIDTH, m_HEIGHT);
	addAndMakeVisible(m_pOpenGLRenderer);
}

MainComponent::~MainComponent()
{
	delete m_pOpenGLRenderer;
}

void MainComponent::paint (Graphics&)
{
	/*
    g.fillAll (Colour (0xffeeddff));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
	*/
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
