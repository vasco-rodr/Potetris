#include "Board.h"

#include <algorithm>

#include "BoardDifficulty.h"
#include "Piece.h"
#include "PiecePooler.h"
#include "ServiceLocator.h"

static const uint8_t MIN_MATCHED_PIECES = 4;

Board::Board() {
	_currentDeltaTime = 0;
	_activeTime = ACTIVE_MOVE_TIME;
	_idleTime = IDLE_MOVE_TIME;
	
	_isControllingPair = false;
	_isGameOver = false;

	_boardDifficulty = std::make_unique<BoardDifficulty>();
	_piecePooler = std::make_unique<PiecePooler>(MAX_COLS * MAX_ROWS);

	_piecesToRemove.reserve(MAX_COLS * MAX_ROWS);

	_grid = std::array<std::array<std::shared_ptr<Piece>, MAX_ROWS>, MAX_COLS>();

	spawnPair();
}

Board::~Board() {
	_piecesToRemove.clear();
	_piecesToRemove.shrink_to_fit();

	for (auto& row : _grid) {
		for (auto& piece : row) {
			piece = nullptr;
		}
	}
}

void Board::render() {
	for (const auto& row : _grid) {
		for (const auto& piece : row) {
			if (piece != nullptr) {
				piece->render();
			}
		}
	}

	if(_isControllingPair) {
		_spawnedPieces.first->render();
		_spawnedPieces.second->render();
	}
}

void Board::update(const uint32_t deltaTime) {
	_currentDeltaTime += deltaTime;

	if (_isControllingPair) {
		if (_currentDeltaTime >= _boardDifficulty->getMoveTime()) {
			if (isSpawnedPairPlaced()) {
				_isControllingPair = false;
				SDL_Point firstPiecePosition = _spawnedPieces.first->getBoardPosition();
				SDL_Point secondPiecePosition = _spawnedPieces.second->getBoardPosition();
				_grid[firstPiecePosition.x][firstPiecePosition.y] = _spawnedPieces.first;
				_grid[secondPiecePosition.x][secondPiecePosition.y] = _spawnedPieces.second;

			} else {
				makeSpawnedPairFall();
				_currentDeltaTime = 0;
			}
		}

	} else {
		if (_currentDeltaTime >= _idleTime) {
			if (!makePiecesFall()) {
				if (searchMatches()) {
					ServiceLocator::getScoreManager()->updateScore(static_cast<uint8_t>(_piecesToRemove.size()));
					removeMatches();

				} else {
					spawnPair();
				}
			}

			_currentDeltaTime = 0;
		}
	}

	_boardDifficulty->update();
}

void Board::makeSpawnedPairFallFaster() {
	if (!isSpawnedPairPlaced())
		makeSpawnedPairFall();
}

void Board::moveSpawnedPairSideways(const MoveDirection moveDirection) {
	const SDL_Point firstPiecePosition = _spawnedPieces.first->getBoardPosition();
	const SDL_Point secondPiecePosition = _spawnedPieces.second->getBoardPosition();

	const int8_t moveFactor = static_cast<int8_t>(moveDirection);

	if (canMoveToPosition(firstPiecePosition.x + moveFactor, firstPiecePosition.y)
		&& canMoveToPosition(secondPiecePosition.x + moveFactor, secondPiecePosition.y)) {
		_spawnedPieces.first->setBoardPosition(firstPiecePosition.x + moveFactor, firstPiecePosition.y);
		_spawnedPieces.second->setBoardPosition(secondPiecePosition.x + moveFactor, secondPiecePosition.y);
	}
}

void Board::rotateSpawnedPair(const RotationType rotationType) {
	const int8_t rotationFactor = static_cast<int8_t>(rotationType);
	
	SDL_Point positionToMove;
	const SDL_Point firstPiecePosition = _spawnedPieces.first->getBoardPosition();
	const SDL_Point secondPiecePosition = _spawnedPieces.second->getBoardPosition();

	if (firstPiecePosition.y == secondPiecePosition.y) {
		positionToMove.x = firstPiecePosition.x;

		if (firstPiecePosition.x < secondPiecePosition.x) {
			positionToMove.y = secondPiecePosition.y - rotationFactor;
		} else {
			positionToMove.y = secondPiecePosition.y + rotationFactor;
		}
		
	} else {
		positionToMove.y = firstPiecePosition.y;

		if (firstPiecePosition.y < secondPiecePosition.y) {
			positionToMove.x = secondPiecePosition.x + rotationFactor;
		} else {
			positionToMove.x = secondPiecePosition.x - rotationFactor;
		}
	}

	if (canMoveToPosition(positionToMove.x, positionToMove.y)) {
		_spawnedPieces.second->setBoardPosition(positionToMove.x, positionToMove.y);
	}
}

bool Board::canMoveToPosition(const int8_t col, const int8_t row) {
	if (!isGameAreaPosition(col, row) || (_grid[col][row] != nullptr)) {
		return false;
	}

	return true;
}

bool Board::isGameAreaPosition(const int8_t col, const int8_t row) {
	if ((col >= MAX_COLS)
		|| (col < 0)
		|| (row >= MAX_ROWS)
		|| (row < 0)) {
		return false;
	}

	return true;
}

void Board::movePieceToPosition(const std::shared_ptr<Piece>& piece, const uint8_t col, const uint8_t row) {
	const SDL_Point position = piece->getBoardPosition();
	piece->setBoardPosition(col, row);
	_grid[col][row] = piece;
	_grid[position.x][position.y] = nullptr;
}

void Board::spawnPair() {

	if ((_grid[LEFT_STARTING_COL][STARTING_ROW] != nullptr) 
		|| (_grid[LEFT_STARTING_COL + 1][STARTING_ROW] != nullptr)) {
		_isGameOver = true;
		return;
	}

	std::shared_ptr<Piece> leftPiece = spawnPieceAtPosition(LEFT_STARTING_COL, STARTING_ROW);
	std::shared_ptr<Piece> rightPiece = spawnPieceAtPosition(LEFT_STARTING_COL + 1, STARTING_ROW);

	_spawnedPieces = std::make_pair(leftPiece, rightPiece);

	_isControllingPair = true;
}

std::shared_ptr<Piece> Board::spawnPieceAtPosition(const uint8_t col, const uint8_t row) {
	std::shared_ptr<Piece> piece = _piecePooler->getPiece();
	piece->setBoardPosition(col, row);
	piece->initialize();

	return piece;
}

bool Board::isSpawnedPairPlaced() {
	const SDL_Point firstPiecePosition = _spawnedPieces.first->getBoardPosition();
	const SDL_Point secondPiecePosition = _spawnedPieces.second->getBoardPosition();

	//Check if pair reached the bottom of the grid
	if ((firstPiecePosition.y == 0) || (secondPiecePosition.y == 0)) {
		return true;
	}
	
	//If one of the pieces cannot fall, the pair is considered placed
	return (_grid[firstPiecePosition.x][firstPiecePosition.y - 1] != nullptr)
		   || (_grid[secondPiecePosition.x][secondPiecePosition.y - 1] != nullptr);
}

void Board::makeSpawnedPairFall() {
	const SDL_Point firstPiecePosition = _spawnedPieces.first->getBoardPosition();
	const SDL_Point secondPiecePosition = _spawnedPieces.second->getBoardPosition();

	_spawnedPieces.first->setBoardPosition(firstPiecePosition.x, firstPiecePosition.y - 1);
	_spawnedPieces.second->setBoardPosition(secondPiecePosition.x, secondPiecePosition.y - 1);
}

bool Board::makePiecesFall() {
	bool piecesFell = false;
	
	for (uint8_t row = 0; row < MAX_ROWS - 1; row++) {
		for (uint8_t col = 0; col < MAX_COLS; col++) {
			if (_grid[col][row] != nullptr) {
				continue;
			}

			//Check if row above has a piece to fall
			if (_grid[col][row + 1] != nullptr) {
				movePieceToPosition(_grid[col][row + 1], col, row);
				piecesFell = true;
			}
		}
	}

	return piecesFell;
}

bool Board::isGameOver() const {
	return _isGameOver;
}

bool Board::searchMatches() {
	for (uint8_t row = 0; row < MAX_ROWS; row++) {
		for (uint8_t col = 0; col < MAX_COLS; col++) {

			if (_grid[col][row] == nullptr) {
				continue;
			}

			if (std::find(_piecesToRemove.begin(), _piecesToRemove.end(), _grid[col][row]) != _piecesToRemove.end()) {
				continue;
			}

			std::vector<std::shared_ptr<Piece>> checkedPieces;
			std::vector<std::shared_ptr<Piece>> matchedPieces;

			searchPieces(col, row, _grid[col][row]->getPieceColor(), checkedPieces, matchedPieces);

			if (matchedPieces.size() >= MIN_MATCHED_PIECES) {
				_piecesToRemove.insert(_piecesToRemove.end(), matchedPieces.begin(), matchedPieces.end());
			}
		}
	}

	return !_piecesToRemove.empty();
}

void Board::searchPieces(const int8_t col,
                         const int8_t row,
                         const PieceColor color,
                         std::vector<std::shared_ptr<Piece>>& checkedPieces,
                         std::vector<std::shared_ptr<Piece>>& matchedPieces) {

	if ((!isGameAreaPosition(col, row) || (_grid[col][row] == nullptr))) {
		return;
	}

	if (std::find(checkedPieces.begin(), checkedPieces.end(), _grid[col][row]) != checkedPieces.end()) {
		return; //Piece was already checked
	}

	checkedPieces.push_back(_grid[col][row]);

	if (_grid[col][row]->getPieceColor() == color) {
		matchedPieces.push_back(_grid[col][row]);

		searchPieces(col - 1, row, color, checkedPieces, matchedPieces);
		searchPieces(col + 1, row, color, checkedPieces, matchedPieces);
		searchPieces(col, row - 1, color, checkedPieces, matchedPieces);
		searchPieces(col, row + 1, color, checkedPieces, matchedPieces);
	}
}

void Board::removeMatches() {
	for (const auto& piece : _piecesToRemove) {
		piece->setVisibility(false);

		const SDL_Point position = piece->getBoardPosition();
		_grid[position.x][position.y] = nullptr;
		
		_piecePooler->setPiece(piece);
	}

	_piecesToRemove.clear();
	_piecesToRemove.shrink_to_fit();
}

void Board::handleKeyPress(const SDL_Keycode key) {

	if (!_isControllingPair) {
		return;
	}

	switch (key) {
		case SDLK_RIGHT:
		case SDLK_d:
			moveSpawnedPairSideways(MoveDirection::Right);
			break;

		case SDLK_LEFT:
		case SDLK_a:
			moveSpawnedPairSideways(MoveDirection::Left);
			break;

		case SDLK_DOWN:
		case SDLK_s:
			makeSpawnedPairFallFaster();
			break;

		case SDLK_LCTRL:
		case SDLK_RCTRL:
			rotateSpawnedPair(RotationType::Clockwise);
			break;

		case SDLK_LSHIFT:
		case SDLK_RSHIFT:
			rotateSpawnedPair(RotationType::CounterClockwise);
			break;
			
		default: 
			break;
	}
}
