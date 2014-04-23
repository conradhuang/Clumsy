#ifndef __MOVE_DIRECTION_RED_H__
#define __MOVE_DIRECTION_RED_H__

#include <cassert>
#include "Board.h"
#include "Common.h"
#include "Types.h"

class MoveDirectionRed
{
public:

	static Pos MoveForward(const Pos a_currentPos)
	{
		return a_currentPos - 10;
	}

	static Pos MoveBackward(const Pos a_currentPos)
	{
		return a_currentPos + 10;
	}

	static Pos MoveLeft(const Pos a_currentPos)
	{
		return a_currentPos - 1;
	}

	static Pos MoveRight(const Pos a_currentPos)
	{
		return a_currentPos + 1;
	}

	static bool IsEnemyTerritory(const Pos a_pos)
	{
		assert(!Board::IsBoundary(a_pos));

		return Board::IsBlkTerritory(a_pos);
	}

	static bool IsEnemy(Chess a_chess)
	{
		return (a_chess >= BLK_PAWN_1) && (a_chess <= BLK_KING);
	}

	static Pos CenterOfPalace()
	{
		return L95;
	}

    static bool IsEnemyKing(Chess a_chess)
    {
        return a_chess == BLK_KING;
    }

    static Chess EnemyKing()
    {
        return BLK_KING;
    }

    static Pos s_kingPos[BOARD_SIZE][MAX_KING_POS + 1];
};

#endif // ifndef __MOVE_DIRECTION_RED_H__