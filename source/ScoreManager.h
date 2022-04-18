/**
 * @file	ScoreManager.h.
 *
 * Declares the ScoreManager class.
 *
 * Manages the current score and the record scores.
 */

#pragma once

#include <SDL.h>
#include <string>
#include <vector>

 /**
  * Struct that represents a high score.
  */
struct HighScore {
	std::string _date;
	uint64_t _score;

	HighScore(std::string date, uint64_t score) {
		_date = date;
		_score = score;
	}
	
	bool operator <(const HighScore& highScore) const {
		return (_score < highScore._score);
	}
};

class ScoreManager {
public:
	ScoreManager();
	~ScoreManager();

	/**
	 * Initializes the score for a new game.
	 */
	void resetScore();

	/**
	 * Updates the current score with the earned points.
	 *
	 * @param numberPiecesRemoved The total of pieces removed.
	 */
	void updateScore(const uint8_t numberPiecesRemoved);

	/**
	 * Gets the current score.
	 *
	 * @return	The score.
	 */
	uint64_t getScore() const;

	/**
	 * Gets the list of high scores.
	 *
	 * @return	The high scores.
	 */
	std::vector<HighScore> getHighScores() const;

	/**
	 * Saves to the vector of high scores the latest game score,
	 * if it is equal or bigger than any existing score.
	 *
	 * @param score the score to save
	 */
	void saveScore();

private:
	/**
	 * Read the high scores saved in the file.
	 *
	 * @return true if the file could be read, false otherwise.
	 */
	bool readScoresFile();

	/**
	 * Saves the scores to the file.
	 */
	void saveScoresFile();
	
	uint64_t _score;
	std::vector<HighScore> _highScores;
};
