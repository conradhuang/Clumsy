#ifndef __MOVE_DIRECTION_BLACK_H__
#define __MOVE_DIRECTION_BLACK_H__

#include "Board.h"
#include "Common.h"
#include "Types.h"

class MoveDirectionBlack
{
public:

	static Pos MoveForward(const Pos a_currentPos)
	{
		return a_currentPos + 10;
	}

	static Pos MoveBackward(const Pos a_currentPos)
	{
		return a_currentPos - 10;
	}

	static Pos MoveLeft(const Pos a_currentPos)
	{
		return a_currentPos + 1;
	}

	static Pos MoveRight(const Pos a_currentPos)
	{
		return a_currentPos - 1;
	}

	static bool IsEnemyTerritory(const Pos a_pos)
	{
		assert(!Board::IsBoundary(a_pos));

		return Board::IsRedTerritory(a_pos);
	}

	static bool IsEnemy(Chess a_chess)
	{
		return (a_chess >= RED_PAWN_1) && (a_chess <= RED_KING);
	}

	static Pos CenterOfPalace()
	{
		return L25;
	}

    static bool IsEnemyKing(Chess a_chess)
    {
        return a_chess == RED_KING;
    }

    static Chess EnemyKing()
    {
        return RED_KING;
    }

    static Pos s_kingPos[BOARD_SIZE][MAX_KING_POS + 1];
};

#endif // ifndef __MOVE_DIRECTION_BLACK_H__