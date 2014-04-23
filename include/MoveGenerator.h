#ifndef __MOVE_GENERATOR_H__
#define __MOVE_GENERATOR_H__

#include "Common.h"
#include "Types.h"

class Board;
class Moves;
class Piece;

class MoveGenerator
{
public:

	static void Init();
	static void Release();

	MoveGenerator();
	~MoveGenerator();

	uint8 GenerateRedMoves(Board &a_board);
    uint8 GenerateRedCaptureMoves(Board &a_board);
	uint8 GenerateBlkMoves(Board &a_board);
    uint8 GenerateBlkCaptureMoves(Board &a_board);

	const MovePos *GetMove(uint8 a_index) const;

    static uint64 s_clocksByChess[MAX_CHESS];

private:

	void GenerateMoves(Chess a_chess, Board &a_board);
    void GenerateCaptureMoves(Chess a_chess, Board &a_board);

	Moves *m_moves;

	static Piece *s_generatorByType[MAX_CHESS_TYPE];
	static Piece *s_generatorByChess[MAX_CHESS];
};

#endif // ifndef __MOVE_GENERATOR_H__