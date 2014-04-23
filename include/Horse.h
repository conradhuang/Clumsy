#ifndef __HORSE_H__
#define __HORSE_H__

#include <cassert>
#include "Moves.h"
#include "Piece.h"

enum
{
    MAX_LEG = 4,
    MAX_HORSE_POS = 8
};

extern Pos g_horseLeg[BOARD_SIZE][MAX_LEG];
extern Pos g_horsePos[BOARD_SIZE][MAX_HORSE_POS];

template <typename MoveDirection>
class Horse : public Piece
{
public:

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
        for (int32 i = 0; i < MAX_LEG && g_horseLeg[a_currentPos][i]; ++i)
        {
            if (!a_board.IsEmpty(g_horseLeg[a_currentPos][i]))
            {
                continue;
            }

            Pos destPos = g_horsePos[a_currentPos][i * 2];

            assert(destPos != 0);

            if (a_board.IsEmpty(destPos))
            {
                a_outMoves.AppendNonTakeMove(a_currentPos, destPos);
            }
            else if (MoveDirection::IsEnemy(a_board[destPos]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, destPos);
            }

            destPos = g_horsePos[a_currentPos][i * 2 + 1];

            if (!destPos)
            {
                continue;
            }

            if (a_board.IsEmpty(destPos))
            {
                a_outMoves.AppendNonTakeMove(a_currentPos, destPos);
            }
            else if (MoveDirection::IsEnemy(a_board[destPos]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, destPos);
            }
        }
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        for (int32 i = 0; i < MAX_LEG && g_horseLeg[a_currentPos][i]; ++i)
        {
            if (!a_board.IsEmpty(g_horseLeg[a_currentPos][i]))
            {
                continue;
            }

            Pos destPos = g_horsePos[a_currentPos][i * 2];

            assert(destPos != 0);

            if (MoveDirection::IsEnemy(a_board[destPos]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, destPos);
            }

            destPos = g_horsePos[a_currentPos][i * 2 + 1];

            if (!destPos)
            {
                continue;
            }

            if (MoveDirection::IsEnemy(a_board[destPos]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, destPos);
            }
        }
    }
};

#endif // #ifndef __HORSE_H__