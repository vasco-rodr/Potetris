/**
 * @file	AudioManager.h.
 *
 * Declares the Audio Manager class.
 *
 * Handles playing sound effects and music.
 */

#pragma once

class AudioManager {

public:
	/**
	 * AudioManager constructor.
	 * 
	 * @param initResult  Out parameter with the result of SDL_mixer's initialization.
	 */
	AudioManager(bool& initResult);

	~AudioManager();

	/**
	 * Plays the specified sound.
	 *
	 * @param soundName	Name of the sound.
	 */
	void playSound(const char* soundName);

	/**
	 * Plays background music.
	 */
	void playMusic();

	/**
	 * Pauses or resumes the music, accordingly to its state.
	 *
	 * @return	True if resumed the music, false if it paused.
	 */
	bool toggleMusic();

private:
	/**
	 * Initializes SDL_mixer.
	 *
	 * @return	true if SDL_mixer was initialized correctly, false otherwise.
	 */
	bool initialize();
};
