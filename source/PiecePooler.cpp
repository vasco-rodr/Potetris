#include "PiecePooler.h"

#include "Piece.h"

PiecePooler::PiecePooler(const uint8_t poolSize) {
	for (uint8_t i = 0; i < poolSize; i++) {
		_piecePool.push(std::make_shared<Piece>());
	}
}

PiecePooler::~PiecePooler() {
	std::stack<std::shared_ptr<Piece>>().swap(_piecePool);
}

std::shared_ptr<Piece> PiecePooler::getPiece() {
	std::shared_ptr<Piece> piece;

	if (_piecePool.empty()) {
		piece = std::make_shared<Piece>();
	} else {
		piece = _piecePool.top();
		_piecePool.pop();
	}

	return piece;
}

void PiecePooler::setPiece(const std::shared_ptr<Piece>& piece) {
	if (piece != nullptr) {
		_piecePool.push(piece);
	}
}
