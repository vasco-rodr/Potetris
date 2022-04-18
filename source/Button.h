/**
 * @file	Button.h.
 *
 * Declares the Button class.
 */

#pragma once

#include <SDL.h>
#include <functional>
#include <memory>


#include "GameObject.h"

class Button : public GameObject {

public:

	/**
	 * Button constructor.
	 *
	 * @param mainTexture		The main texture of the button.
	 * @param secondaryTexture	The secondary texture of the button, to use if the button toggles.
	 */
	Button(std::shared_ptr<SDL_Texture> mainTexture, std::shared_ptr<SDL_Texture> secondaryTexture);

	~Button();

	/**
	 * Executes the button action.
	 */
	void onClick();

	/**
	 * Sets the button's action.
	 * 
	 * @param action The action executed on click.
	 */
	void setAction(const std::function<void()>& action);

	/**
	 * Updates the button's state.
	 *
	 */
	void update();

private:
	/**
	 * Checks if a given position is inside the button.
	 *
	 * @param position The position to be checked.
	 */
	bool isPositionInButton(const SDL_Point position) const;

	/**
	 * Sets the hovered state.
	 *
	 * @param isHovered If the button is being hovered by the mouse or not.
	 */
	void setIsHovered(const bool isHovered);

	/**
	 * Changes the button's texture between the main and secondary textures.
	 */
	void swapTexture();

	bool _isHovered;
	bool _wasPressed;

	std::function<void()> _action;

	std::shared_ptr<SDL_Texture> _mainTexture;
	std::shared_ptr<SDL_Texture> _secondaryTexture;
};