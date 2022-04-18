/**
 * @file	MouseManager.h.
 *
 * Declares the Mouse Manager class.
 * 
 * Manages mouse events.
 */

#pragma once

#include <SDL.h>

 /**
  * Values that represent the possible states of the mouse's buttons.
  */
enum class MouseState {
	ButtonDown,
	ButtonUp
};

class MouseManager {

public:
	MouseManager();
	~MouseManager();

	/**
	 * Gets the current position of the mouse.
	 *
	 * @return	The position.
	 */
	SDL_Point getPosition() const;

	/**
	 * Checks if the left mouse button is pressed.
	 *
	 * @return	True if pressed, false if not.
	 */
	bool isLeftButtonPressed() const;

	/**
	 * Treats mouse input.
	 *
	 * @param event The SDL mouse event.
	 */
	void handleEvent(SDL_Event &event);

	/**
	 * Updates the mouse's state in each frame.
	 */
	void updateState();

private:
	/**
	 * Handles the mouse move event.
	 *
	 * @param event The SDL mouse event.
	 */
	void onMouseMove(SDL_Event& event);

	/**
	 * Handles the mouse button down event.
	 *
	 * @param event The SDL mouse event.
	 */
	void onMouseButtonDown(SDL_Event& event);

	/**
	 * Handles the mouse button up event.
	 *
	 * @param event The SDL mouse event.
	 */
	void onMouseButtonUp(SDL_Event& event);
	
	MouseState _currentFrameState;
	MouseState _pastFrameState;
	SDL_Point _position;
};