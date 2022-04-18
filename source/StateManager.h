/**
 * @file	StateManager.h.
 *
 * Declares the StateManager class.
 *
 * Manages the application state.
 */

#pragma once

#include <SDL.h>
#include <memory>

class Screen;
enum class ApplicationState : uint8_t;

class StateManager {
public:
	StateManager();
	~StateManager();

	/**
	 * Sets the application state.
	 *
	 * @param applicationState	State to be displayed by the application.
	 */
	void changeState(ApplicationState applicationState);

	/**
	 * Runs the manager's actions.
	 */
	void run();

	/**
	 * Forwards the keyboard input event to the active screen.
	 *
	 * @param event Keyboard input event.
	 */
	void handleKeyboardInput(SDL_Event& event) const;

private:
	/**
	 * Checks the active screen and the application state, and changes
	 * the active screen if it is different from the application state.
	 */
	void pushState();

	ApplicationState _applicationState;
	std::unique_ptr<Screen> _activeScreen;
};