/**
 * @file	HighScoresScreen.h.
 *
 * Declares the HighScoresScreen class.
 *
 * Represents the screen where the high scores can be seen.
 */

#pragma once

#include <SDL.h>
#include <memory>

#include "Screen.h"

class Button;

class HighScoresScreen : public Screen {

public:
	HighScoresScreen();
	~HighScoresScreen();

	void handleKeyPress(const SDL_Keycode key) override;

private:
	void renderHighScores() const;
	void renderScreenSpecificElements() override;
	void update() override;

	std::unique_ptr<Button> _backButton;
};
