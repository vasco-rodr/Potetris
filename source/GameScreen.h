/**
 * @file	GameScreen.h.
 *
 * Declares the GameScreen class.
 *
 * Represents the screen where the game is played.
 */

#pragma once

#include <SDL.h>
#include <memory>

#include "Screen.h"

class Board;
class Button;
class Timer;

class GameScreen : public Screen {

public:
	GameScreen();
	~GameScreen();

	void handleKeyPress(const SDL_Keycode key) override;
	
private:
	/**
	 * Setups the togglePause button's visual aspect, position and action.
	 */
	void initializePauseButton();

	/**
	 * Setups the sound button's visual aspect, position and action.
	 */
	void initializeSoundButton();

	/*
	 * Pauses/unpauses the game.
	 */
	void togglePause();

	/*
	 * Displays the current score on the screen. 
	 */
	void renderScore() const;
	
	void renderScreenSpecificElements() override;
	void update() override;

	std::shared_ptr<SDL_Texture> _pauseTexture;
	
	std::unique_ptr<Board> _board;
	std::unique_ptr<Button> _pauseButton, _soundButton;

	std::unique_ptr<Timer> _timer;
	uint32_t _updateTime{};
	bool _isPaused;
};