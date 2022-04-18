/**
 * @file	GameObject.h.
 *
 * Declares the Game Object class.
 */

#pragma once

#include <memory>
#include <SDL.h>

class GameObject {

public:
	GameObject();
	virtual ~GameObject();

	/**
	 * Initializes the game object.
	 */
	virtual void initialize();

	/**
	 * Updates the status of the game object.
	 */
	virtual void update();

	/**
	 * Renders the game object.
	 */
	void render() const;

	/**
	 * Sets the texture of the game object.
	 *
	 * @param  texture	The texture.
	 */
	void setTexture(std::shared_ptr<SDL_Texture> texture);

	/**
	 * Gets the position of the game object.
	 *
	 * @return	The position.
	 */
	SDL_Point getPosition() const;

	/**
	 * Sets the position of the game object.
	 *
	 * @param position	The position.
	 */
	void setPosition(const SDL_Point position);

	/**
	 * Sets the position of the game object.
	 *
	 * @param x	The x coordinate.
	 * @param y	The y coordinate.
	 */
	void setPosition(const int x, const int y);

	/**
	 * Sets the visibility state of the game object.
	 *
	 * @param isVisible	True if is visible, false if not.
	 */
	void setVisibility(const bool isVisible);

	/**
	 * Checks if the game object is visible.
	 *
	 * @return	True if visible, false if not.
	 */
	bool isVisible() const;

	/**
	 * Gets the width of the game object.
	 *
	 * @return	The width of the object.
	 */
	int getWidth() const;

	/**
	 * Gets the height of the game object.
	 *
	 * @return	The height of the object.
	 */
	int getHeight() const;

protected:
	bool _isVisible;

	SDL_Point _position;

	std::shared_ptr<SDL_Texture> _texture;

	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;
};