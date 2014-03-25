#include "SoundManager.h"

namespace sound
{
	SoundManager::SoundManager(){
		m_pDeviceManager = new AudioDeviceManager();
		m_pDeviceManager->initialise(0, 2, nullptr, true);
		m_formatManager.registerBasicFormats();
		
		m_pTransportSource = new juce::AudioTransportSource();
		m_pTransportSource->setGain(50);
		juce::File fileSound = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/sound/particle.mp3");
		if(!fileSound.existsAsFile()){
			std::cout << "Error when loading texture of the sound." << std::endl;
		}
		loadFileIntoTransport(fileSound);

		m_pAudioSourcePlayer = new AudioSourcePlayer();
        m_pDeviceManager->addAudioCallback(m_pAudioSourcePlayer);
        m_pAudioSourcePlayer->setSource(m_pTransportSource);
	}

	SoundManager::~SoundManager(){
        m_pTransportSource->setSource(nullptr);
        m_pAudioSourcePlayer->setSource(nullptr);
        m_pDeviceManager->removeAudioCallback(m_pAudioSourcePlayer);
		delete m_pTransportSource;
		delete m_pAudioSourcePlayer;
		delete m_pDeviceManager;
	}

	void SoundManager::loadFileIntoTransport(const File& audioFile) {
        // unload the previous file source and delete it..
        m_pTransportSource->stop();
        m_pTransportSource->setSource(nullptr);
        m_currentAudioFileSource = nullptr;

        AudioFormatReader* reader = m_formatManager.createReaderFor(audioFile);

        if (reader != nullptr)
        {
            m_currentAudioFileSource = new AudioFormatReaderSource(reader, true);

            // ..and plug it into our transport source
            m_pTransportSource->setSource(m_currentAudioFileSource);
        }
    }

	void SoundManager::playSound(){
		m_pTransportSource->setPosition(0);
		m_pTransportSource->start();
	}
}