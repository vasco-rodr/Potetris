/**
 * @file	HelpScreen.h.
 *
 * Declares the HelpScreen class.
 *
 * Represents the screen where the instructions can be seen.
 */

#pragma once

#include <SDL.h>
#include <memory>

#include "Screen.h"

class Button;

class HelpScreen : public Screen {

public:
	HelpScreen();
	~HelpScreen();

	void handleKeyPress(const SDL_Keycode key) override;

private:
	void renderScreenSpecificElements() override;
	void update() override;

	std::unique_ptr<Button> _backButton;
};
