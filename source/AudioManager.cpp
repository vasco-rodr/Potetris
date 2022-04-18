#include "AudioManager.h"

#include <SDL_mixer.h>
#include <iostream>

#include "ServiceLocator.h"
#include "Settings.h"

static const uint8_t OPENAUDIO_CHANNELS = 2;
static const uint16_t OPENAUDIO_FREQUENCY = 44100;
static const uint16_t OPENAUDIO_CHUNKSIZE = 2048;
static const int8_t OPENAUDIO_ALL_CHANNELS = -1;

AudioManager::AudioManager(bool& initResult) {
	initResult = initialize();
}

AudioManager::~AudioManager() {
	Mix_HaltMusic();
	Mix_HaltChannel(OPENAUDIO_ALL_CHANNELS);
	Mix_Quit();
}

bool AudioManager::initialize() {
	if (Mix_OpenAudio(OPENAUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, OPENAUDIO_CHANNELS, OPENAUDIO_CHUNKSIZE) < 0) {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioManager::playSound(const char* soundName) {
	Mix_PlayChannel(-1, ServiceLocator::getResourceManager()->loadSound(soundName).get(), 0);
}

void AudioManager::playMusic() {
	Mix_PlayMusic(ServiceLocator::getResourceManager()->loadMusic(MUSIC).get() , -1);
}

bool AudioManager::toggleMusic() {
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
		return true;
	} else {
		Mix_PauseMusic();
		return false;
	}
}