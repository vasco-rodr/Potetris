/**
 * @file	MenuScreen.h.
 *
 * Declares the MenuScreen class.
 *
 * Represents the first screen seen upon launching the game.
 */

#pragma once

#include <SDL.h>
#include <memory>

#include "Screen.h"

class Button;

class MenuScreen : public Screen {

public:
	MenuScreen();
	~MenuScreen();

	void handleKeyPress(const SDL_Keycode key) override;

private:
	void renderScreenSpecificElements() override;
	void update() override;

	std::unique_ptr<Button> _howToButton;
	std::unique_ptr<Button> _highScoresButton;
	std::unique_ptr<Button> _playButton;
};
