/**
 * @file	BoardDifficulty.h.
 *
 * Declares the BoardDifficulty class.
 *
 * Manages the difficulty of the board.
 */

#pragma once

#include <cstdint>

class BoardDifficulty {
public:
	BoardDifficulty();
	~BoardDifficulty();

	/**
	 * Updates the difficulty according to the current score.
	 */
	void update();

	/**
	 * Gets the time needed until the pair of pieces moves down.
	 *
	 * @return	the time.
	 */
	uint32_t getMoveTime() const;

private:
	/**
	 * Increases the difficulty of the board.
	 */
	void increaseDifficulty();
	
	uint8_t _currentLevel;
	uint32_t _moveTime;
	uint32_t _scoreToNextLevel;
};