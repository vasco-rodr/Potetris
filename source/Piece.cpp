#include "Piece.h"

#include "ServiceLocator.h"
#include "Settings.h"

Piece::Piece() {
	_color = PieceColor();
	_boardPosition = SDL_Point();
	_destinationRect.w = PIECE_SIZE;
	_destinationRect.h = PIECE_SIZE;
}

Piece::~Piece() {}

void Piece::initialize() {
	_color = PieceColor(rand() % NUMBER_COLORS);
	_texture = getTextureFromColor(_color);

	_isVisible = true;
}

PieceColor Piece::getPieceColor() const {
    return _color;
}

std::shared_ptr<SDL_Texture> Piece::getTextureFromColor(const PieceColor color) {
	switch (color) {
		case PieceColor::Blue:
			return ServiceLocator::getResourceManager()->loadTexture(COLOR_1_TEX);
		case PieceColor::Green:
			return ServiceLocator::getResourceManager()->loadTexture(COLOR_2_TEX);
		case PieceColor::Red:
			return ServiceLocator::getResourceManager()->loadTexture(COLOR_3_TEX);
		case PieceColor::Yellow:
			return ServiceLocator::getResourceManager()->loadTexture(COLOR_4_TEX);
		}
	
	return nullptr;
}

SDL_Point Piece::getBoardPosition() const {
	return _boardPosition;
}

void Piece::setBoardPosition(const uint8_t col, const uint8_t row) {
	_boardPosition.x = col;
	_boardPosition.y = row;
	setPosition(SPAWN_ZONE.x + (col)*PIECE_SIZE, SPAWN_ZONE.y - (row)*PIECE_SIZE);
}
