#include "BoardDifficulty.h"

#include "ServiceLocator.h"
#include "Settings.h"

static const uint8_t TIME_DECREASE = 100;
static const uint8_t SCORE_TO_LEVEL_UP = 50;
static const uint8_t MIN_MOVE_TIME = 100;

BoardDifficulty::BoardDifficulty() {
	_currentLevel = 1;
	_scoreToNextLevel = SCORE_TO_LEVEL_UP;
	_moveTime = ACTIVE_MOVE_TIME;
}

BoardDifficulty::~BoardDifficulty() {}

void BoardDifficulty::update() {
	if(ServiceLocator::getScoreManager()->getScore() > _scoreToNextLevel) {
		increaseDifficulty();
	}
}

void BoardDifficulty::increaseDifficulty() {
	_currentLevel++;
	_scoreToNextLevel += SCORE_TO_LEVEL_UP * _currentLevel;
	uint32_t newMoveTime = _moveTime - TIME_DECREASE;

	if(newMoveTime < MIN_MOVE_TIME) {
		_moveTime = MIN_MOVE_TIME;
	} else {
		_moveTime = newMoveTime;
	}
}

uint32_t BoardDifficulty::getMoveTime() const {
	return _moveTime;
}