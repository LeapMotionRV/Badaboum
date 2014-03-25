#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <JuceHeader.h>

namespace sound
{
	/**
		Manage all the sounds in the game.
	*/
	class SoundManager : public Component
	{
	public:
		/*
		* Represents the id of a specific sound in the array of sounds.
		*/
		enum SoundId{
			BACKGROUND,
			PARTICLE,
			WIND
		};

		SoundManager();
		~SoundManager();

		void loadFileIntoTransport(const File& audioFile, SoundId idOfSound);
		void playSound(SoundId idOfSound);

	private:
		juce::AudioDeviceManager*				m_pDeviceManager;
		juce::AudioFormatManager				m_formatManager;

		std::vector<juce::AudioSourcePlayer*>		m_audioSourcePlayerArray;
		std::vector<juce::AudioTransportSource*>	m_transportSourceArray;

		std::vector<juce::ScopedPointer<juce::AudioFormatReaderSource>> m_currentAudioFileSourceArray;

		 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundManager);
	};
}

#endif //SOUNDMANAGER_H