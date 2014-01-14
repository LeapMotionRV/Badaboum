#include "MainComponent.h"

namespace render
{
	MainComponent::MainComponent()
	{
		setBounds(0, 0, m_WIDTH, m_HEIGHT);

		m_pOpenGLRenderer = new Renderer(m_WIDTH, m_HEIGHT);
		addAndMakeVisible(m_pOpenGLRenderer);
	}

	MainComponent::~MainComponent()
	{
		delete m_pOpenGLRenderer;
	}

	void MainComponent::paint (Graphics&) //g
	{
		// An example of how to display text for a menu before the OpenGL scene
		/*
		g.fillAll (Colours::grey);
		g.setFont (Font(16.0f));
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
}