#ifndef __GUARD_H__
#define __GUARD_H__

#include "Piece.h"

template <typename MoveDirection>
class Guard : public Piece
{
public:

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		if (a_currentPos == MoveDirection::CenterOfPalace())
		{
			Pos offset[] = {-9, +9, -11, +11};

			for (int i = 0; i < (sizeof(offset) / sizeof(offset[0])); ++i)
			{
				if (a_board.IsEmpty(MoveDirection::CenterOfPalace() + offset[i]))
				{
					a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::CenterOfPalace() + offset[i]);
				}
				else if (MoveDirection::IsEnemy(a_board[MoveDirection::CenterOfPalace() + offset[i]]))
				{
					a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::CenterOfPalace() + offset[i]);
				}
			}
		}
		else
		{
			if (a_board.IsEmpty(MoveDirection::CenterOfPalace()))
			{
				a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::CenterOfPalace());
			}
			else if (MoveDirection::IsEnemy(a_board[MoveDirection::CenterOfPalace()]))
			{
				a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::CenterOfPalace());
			}
		}
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        if (a_currentPos == MoveDirection::CenterOfPalace())
        {
            Pos offset[] = {-9, +9, -11, +11};

            for (int i = 0; i < (sizeof(offset) / sizeof(offset[0])); ++i)
            {
                if (MoveDirection::IsEnemy(a_board[MoveDirection::CenterOfPalace() + offset[i]]))
                {
                    a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::CenterOfPalace() + offset[i]);
                }
            }
        }
        else
        {
            if (MoveDirection::IsEnemy(a_board[MoveDirection::CenterOfPalace()]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::CenterOfPalace());
            }
        }
    }
};

#endif // #ifndef __GUARD_H__