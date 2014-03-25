#include "SoundManager.h"

namespace sound
{
	SoundManager::SoundManager(){
		m_pDeviceManager = new juce::AudioDeviceManager();
		m_pDeviceManager->initialise(0, 2, nullptr, true);
		m_formatManager.registerBasicFormats();
		
		//particle sound
		m_transportSourceArray.insert(m_transportSourceArray.begin() + SoundId::PARTICLE, new juce::AudioTransportSource());
		juce::File fileParticleSound = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/sound/particle.mp3");
		if(!fileParticleSound.existsAsFile()){
			std::cout << "Error when loading texture of the sound for the particle." << std::endl;
		}
		loadFileIntoTransport(fileParticleSound, SoundId::PARTICLE);
		m_audioSourcePlayerArray.insert(m_audioSourcePlayerArray.begin() + SoundId::PARTICLE, new juce::AudioSourcePlayer());
		m_pDeviceManager->addAudioCallback(m_audioSourcePlayerArray.at(SoundId::PARTICLE));
		m_audioSourcePlayerArray.at(SoundId::PARTICLE)->setSource(m_transportSourceArray.at(SoundId::PARTICLE));

		//wind sound
		m_transportSourceArray.insert(m_transportSourceArray.begin() + SoundId::WIND, new juce::AudioTransportSource());
		juce::File fileWindSound = juce::File::getCurrentWorkingDirectory().getChildFile("../../data/sound/wind.mp3");
		if(!fileWindSound.existsAsFile()){
			std::cout << "Error when loading texture of the sound for the wind." << std::endl;
		}
		loadFileIntoTransport(fileWindSound, SoundId::WIND);
		m_audioSourcePlayerArray.insert(m_audioSourcePlayerArray.begin() + SoundId::WIND, new juce::AudioSourcePlayer());
		m_pDeviceManager->addAudioCallback(m_audioSourcePlayerArray.at(SoundId::WIND));
		m_audioSourcePlayerArray.at(SoundId::WIND)->setSource(m_transportSourceArray.at(SoundId::WIND));
	}

	SoundManager::~SoundManager(){
		for(size_t i = 0; i < m_transportSourceArray.size(); ++i){
			m_transportSourceArray.at(i)->setSource(nullptr);
			m_audioSourcePlayerArray.at(i)->setSource(nullptr);
			m_pDeviceManager->removeAudioCallback(m_audioSourcePlayerArray.at(i));
			delete m_audioSourcePlayerArray.at(i);
			delete m_transportSourceArray.at(i);
		}
		delete m_pDeviceManager;
	}

	void SoundManager::loadFileIntoTransport(const File& audioFile, SoundId idOfSound) {
        // unload the previous file source and delete it..
        m_transportSourceArray.at(idOfSound)->stop();
        m_transportSourceArray.at(idOfSound)->setSource(nullptr);

        AudioFormatReader* reader = m_formatManager.createReaderFor(audioFile);

        if (reader != nullptr) {
			m_currentAudioFileSourceArray.insert(m_currentAudioFileSourceArray.begin() + idOfSound, 
												 new AudioFormatReaderSource(reader, true));
            //plug it into our transport source
            m_transportSourceArray.at(idOfSound)->setSource(m_currentAudioFileSourceArray.at(idOfSound));
        }
    }

	void SoundManager::playSound(SoundId idOfSound){
		for(size_t i = 0; i < m_transportSourceArray.size(); ++i){
			m_transportSourceArray.at(i)->setPosition(0);
			m_transportSourceArray.at(i)->stop();
		}
		m_transportSourceArray.at(idOfSound)->setPosition(0);
		m_transportSourceArray.at(idOfSound)->start();
	}
}