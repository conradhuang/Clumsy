#ifndef __PIECE_H__
#define __PIECE_H__

#include "Types.h"

class Moves;
class Board;

class Piece
{
public:

	Piece()
	{
	}

	virtual ~Piece() {}

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) = 0;
    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) = 0;
};

#endif // ifndef __PIECE_H__