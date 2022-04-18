#include "ScoreManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "Settings.h"

static const char* DATE_FORMAT = "%d/%m/%Y-%R";
static const uint8_t DATE_STRING_SIZE = 100;
static const uint8_t DATE_STRING_SIZE_BYTES = 50;

ScoreManager::ScoreManager() {
	readScoresFile();
	resetScore();
}

ScoreManager::~ScoreManager() {
	saveScoresFile();
	_highScores.clear();
}

void ScoreManager::resetScore() {
	_score = 0;
}

void ScoreManager::updateScore(const uint8_t numberPiecesRemoved) {
	_score += (numberPiecesRemoved * numberPiecesRemoved);
}

uint64_t ScoreManager::getScore() const {
	return _score;
}

bool ScoreManager::readScoresFile() {

	std::filebuf fileStreamBuffer;
	if (fileStreamBuffer.open(SCORES_FILE, std::ios::in)) {
		std::istream is(&fileStreamBuffer);
		std::string date;
		uint64_t score;

		while (is >> date >> score) {
			_highScores.emplace_back(date, score);
		}

		fileStreamBuffer.close();

		return true;
	}

	return false;
}

std::vector<HighScore> ScoreManager::getHighScores() const {
	return _highScores;
}

void ScoreManager::saveScore() {
	
	if ((_score > 0)
		&& ((_highScores.size() < TOTAL_SCORES)
			|| (_highScores[_highScores.size() - 1]._score < _score))) {
		time_t currentTime;
		time(&currentTime);
		
		tm timeInfo;
		localtime_s(&timeInfo, &currentTime);

		char date_string[DATE_STRING_SIZE];
		strftime(date_string, DATE_STRING_SIZE_BYTES, DATE_FORMAT, &timeInfo);
		const std::string date(date_string);
		
		_highScores.emplace_back(HighScore(date, _score));
	
		std::sort(_highScores.rbegin(), _highScores.rend());

		if (_highScores.size() > TOTAL_SCORES) {
			_highScores.pop_back();
		}
	}
}

void ScoreManager::saveScoresFile() {
	std::ofstream file(SCORES_FILE, std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		for (const auto& highScore : _highScores) {
			file << highScore._date << " " << highScore._score << std::endl;
		}

		file.close();

	} else {
		std::cout << "Error: Unable to save file!" << std::endl;
	}
}