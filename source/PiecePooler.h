/**
 * @file	PiecePooler.h.
 *
 * Declares the Piece Pooler class.
 * 
 * Manages the reuse of pieces, allowing to not have to 
 * create and delete them every time a piece is required.
 */

#pragma once

#include <stack>
#include <memory>

class Piece;

class PiecePooler {

public:

	/**
	 * PiecePooler constructor.
	 *
	 * @param poolSize Size of the pool.
	 */
	PiecePooler(const uint8_t poolSize);

	~PiecePooler();

	/**
	 * Gets a piece from the pooler.
	 *
	 * @return	A piece.
	 */
	std::shared_ptr<Piece> getPiece();

	/**
	 * Saves a piece in the pooler.
	 *
	 * @param piece - The piece to save.
	 */
	void setPiece(const std::shared_ptr<Piece>& piece);

private:
	std::stack<std::shared_ptr<Piece>> _piecePool;
};