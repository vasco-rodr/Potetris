/**
 * @file	Screen.h.
 *
 * Declares the Screen class.
 *
 * Represents a view and its logic.
 */

#pragma once

#include <memory>
#include <SDL.h>

enum class ApplicationState : uint8_t;

class Screen {

public:
	/**
	 * Screen constructor.
	 * 
	 * @param backgroundTexture The background image of the screen.
	 * @param applicationState	The application state associated with the screen.
	 */
	Screen(const char* backgroundTexture, const ApplicationState applicationState);

	virtual ~Screen();

	/**
	 * Renders the base's screen elements.
	 */
	void render();

	/**
	 * Runs the screen's actions.
	 */
	void run();

	/**
	 * Treats keyboard input.
	 *
	 * @param key The key pressed.
	 */
	virtual void handleKeyPress(const SDL_Keycode key) = 0;

	/**
	 * Allows to know what is the application state associated with the screen.
	 *
	 * @return The screen's application state.
	 */
	ApplicationState getState() const;

protected:
	/**
	 * Renders the elements specific to the screen.
	 */
	virtual void renderScreenSpecificElements() = 0;

	/**
	 * Updates the screen's contents.
	 */
	virtual void update() = 0;

private:
	std::shared_ptr<SDL_Texture> _backgroundTexture;
	ApplicationState _state;
};