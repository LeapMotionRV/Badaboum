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
		SoundManager();
		~SoundManager();

		void loadFileIntoTransport(const File& audioFile);
		void playSound();

	private:
		juce::AudioDeviceManager*				m_pDeviceManager;
		juce::AudioFormatManager				m_formatManager;

		juce::AudioSourcePlayer*				m_pAudioSourcePlayer;
		juce::AudioTransportSource*				m_pTransportSource;

		juce::ScopedPointer<juce::AudioFormatReaderSource> m_currentAudioFileSource;

		 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundManager);
	};
}

#endif //SOUNDMANAGER_H