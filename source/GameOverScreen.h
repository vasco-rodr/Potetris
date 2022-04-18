/**
 * @file	GameOverScreen.h.
 *
 * Declares the GameOverScreen class.
 *
 * Represents the screen seen upon losing the game.
 */

#pragma once

#include <SDL.h>
#include <memory>

#include "Screen.h"

class Button;

class GameOverScreen : public Screen {

public:
	GameOverScreen();
	~GameOverScreen();
	
	void handleKeyPress(const SDL_Keycode key) override;

private:
	void renderScreenSpecificElements() override;
	void update() override;

	std::unique_ptr<Button> _quitButton;
};
