/**
 * @file	Piece.h.
 *
 * Declares the Piece class.
 * 
 * The in-game object that should be combined to be destroyed;
 * the core of the game.
 */

#pragma once

#include <memory>

#include "GameObject.h"

/**
 * Values that represent the possible colors of a piece.
 */
enum class PieceColor : uint8_t {
	Blue,
	Green,
	Red,
	Yellow
};

class Piece : public GameObject {

public:
	Piece();
	~Piece();

	/**
	 * Initializes the piece with a random color.
	 */
	void initialize() override;

	/**
	 * Gets the color of the piece.
	 *
	 * @return	The piece's color.
	 */
	PieceColor getPieceColor() const;

	/**
	 * Gets position of the piece in the board.
	 *
	 * @return	The piece's position in the board area.
	 */
	SDL_Point getBoardPosition() const;

	/**
	 * Sets the position of the piece in the board.
	 *
	 * @param col The col in the board area.
	 * @param row The row in the board area.
	 */
	void setBoardPosition(const uint8_t col, const uint8_t row);

private:
	/**
	 * Loads the piece's texture based on the given color.
	 *
	 * @param	color	The color of the piece.
	 *
	 * @return	The texture for the color.
	 */
	static std::shared_ptr<SDL_Texture> getTextureFromColor(const PieceColor color);

	PieceColor _color;
	SDL_Point _boardPosition;
};