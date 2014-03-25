#include "MainComponent.h"
#include "WindowScreen.h"

namespace render
{
	MainComponent::MainComponent()
	{
		setBounds(0, 0, m_WIDTH, m_HEIGHT);

		//create the renderer
		m_pOpenGLRenderer = new Renderer(m_WIDTH, m_HEIGHT);
		addAndMakeVisible(m_pOpenGLRenderer);

		//add the model to the renderer
		m_pModel = new physical::Model();
		m_pOpenGLRenderer->setModel(m_pModel);

		//create the sound, and add it to the renderer and the Leap Motion
		m_pSoundManager = new sound::SoundManager();
		m_pOpenGLRenderer->setSoundManager(m_pSoundManager);

		//add manager for classic inputs (mouse and keyboard)
		m_pInputManager = new input::InputManager(m_pOpenGLRenderer);
		m_pOpenGLRenderer->addMouseListener(m_pInputManager, false);
		m_pOpenGLRenderer->addKeyListener(m_pInputManager);

		//add the listener to the controller (Leap Motion)
		m_pLeapMotionListener = new input::LeapMotionListener(m_pOpenGLRenderer, m_pSoundManager);
		Leap::Controller controller = BadaboumWindow::getController();
		controller.addListener(*m_pLeapMotionListener);
	}

	MainComponent::~MainComponent()
	{
		BadaboumWindow::getController().removeListener(*m_pLeapMotionListener);
		m_pOpenGLRenderer->removeMouseListener(m_pInputManager);
		m_pOpenGLRenderer->removeKeyListener(m_pInputManager);

		delete m_pModel;
		delete m_pOpenGLRenderer;
		delete m_pInputManager;
		delete m_pLeapMotionListener;
	}

	void MainComponent::paint (Graphics& )//g
	{
		// An example of how to display text for a menu before the OpenGL scene
		/*if(m_pOpenGLRenderer->isPaused()){
			g.fillAll (Colours::grey);
			g.setFont (Font(16.0f));
			g.setColour (Colours::black);
			g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
		}*/
		
	}

	void MainComponent::resized()
	{
		// This is called when the MainContentComponent is resized.
		// If you add any child components, this is where you should
		// update their positions.
	}
}