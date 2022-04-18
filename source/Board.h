/**
 * @file	Board.h.
 *
 * Declares the Board class.
 *
 * Manages the gameplay logic.
 */

#pragma once

#include <SDL.h>

#include <array>
#include <memory>
#include <vector>
#include <utility>

#include "Settings.h"

class BoardDifficulty;
class Piece;
class PiecePooler;
enum class PieceColor : uint8_t;

/**
 * Values that represent the rotation direction of a pair of pieces.
 */
enum class RotationType {
	CounterClockwise = -1,
	Clockwise = 1
};

/**
 * Values that represent the moving direction of a pair of pieces.
 */
enum class MoveDirection {
	Left = -1,
	Right = 1
};

class Board {
public:
	Board();
	~Board();

	/**
	 * Renders the board.
	 */
	void render();

	/**
	 * Updates the board.
	 *
	 * @param deltaTime	The time since the last update.
	 */
	void update(const uint32_t deltaTime);

	/**
	 * Checks if the game has reached a game over state.
	 *
	 * @return	True if game over, false if not.
	 */
	bool isGameOver() const;

	/**
	 * Handles the keyboard input.
	 *
	 * @param key The key pressed.
	 */
	void handleKeyPress(const SDL_Keycode key);

private:
	/**
	 * Checks if a position is inside of the board area.
	 *
	 * @param	col	The column.
	 * @param	row	The row.
	 *
	 * @return	True if is inside of the board area, false otherwise.
	 */
	bool isGameAreaPosition(const int8_t col, const int8_t row);

	/**
	 * Tries to spawn a new pair of pieces on the top of the board.
	 */
	void spawnPair();

	/**
	 * Spawns a piece at a given position.
	 *
	 * @param	col	The column position.
	 * @param	row	The row position.
	 *
	 * @return	The new piece.
	 */
	std::shared_ptr<Piece> spawnPieceAtPosition(const uint8_t col, const uint8_t row);

	/**
	 * Checks if any of the pieces of the spawned pair can't fall anymore.
	 *
	 * @return	True if at least one of the pieces can't fall, false otherwise.
	 */
	bool isSpawnedPairPlaced();

	/**
	 * Moves the spawned pair downwards in the board.
	 */
	void makeSpawnedPairFall();

	/**
	 * Moves pieces of the board downwards, given there is at least one empty position below it.
	 *
	 *  @return	True if at least one piece fell, false otherwise.
	 */
	bool makePiecesFall();

	/**
	 * Checks if a piece can be moved to a position.
	 *
	 * @param	col	The column position.
	 * @param	row	The row position.
	 *
	 * @return	True if it can be moved, false otherwise.
	 */
	bool canMoveToPosition(const int8_t col, const int8_t row);

	/**
	 * Moves a piece to a position.
	 *
	 * @param	piece	The piece to be moved.
	 * @param	col		The column position.
	 * @param	row		The row position.
	 */
	void movePieceToPosition(const std::shared_ptr<Piece>& piece, const uint8_t col, const uint8_t row);

	/**
	 * Rotates the spawned pair of pieces.
	 *
	 * @param	rotationType	The direction to rotate the pair.
	 */
	void rotateSpawnedPair(const RotationType rotationType);

	/**
	 * Moves the spawned pair of pieces to the side.
	 *
	 * @param	moveDirection	The direction to move the pair to.
	 */
	void moveSpawnedPairSideways(const MoveDirection moveDirection);

	/**
	 * Moves the spawned pair downwards in the board every time it's called.
	 */
	void makeSpawnedPairFallFaster();

	/**
	 * Searches for groups of pieces that can be removed in the entire board area.
	 * 
	 * @return	True if at least one match is found, false otherwise.
	 */
	bool searchMatches();

	/**
	 * Searches for pieces that make a match with the piece on a given position.
	 *
	 * @param	col				The column position where to start the search.
	 * @param	row				The row position where to start the search.
	 * @param	color			The color to search for.
	 * @param	checkedPieces	Pieces that have already been searched.
	 * @param	matchedPieces	Pieces that were found as matches.
	 */
	void searchPieces(const int8_t col,
	                  const int8_t row,
	                  const PieceColor color,
	                  std::vector<std::shared_ptr<Piece>>& checkedPieces,
	                  std::vector<std::shared_ptr<Piece>>& matchedPieces);

	/**
	 * Removes all of the pieces found as matches.
	 */
	void removeMatches();

	uint32_t _currentDeltaTime;
	uint32_t _activeTime;
	uint32_t _idleTime;

	bool _isGameOver;
	bool _isControllingPair;

	std::unique_ptr<BoardDifficulty> _boardDifficulty;
	std::unique_ptr<PiecePooler> _piecePooler;
	
	std::array<std::array<std::shared_ptr<Piece>, MAX_ROWS>, MAX_COLS> _grid;
	std::vector<std::shared_ptr<Piece>> _piecesToRemove;
	std::pair<std::shared_ptr<Piece>, std::shared_ptr<Piece>> _spawnedPieces;
};