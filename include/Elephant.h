#ifndef __ELEPHANT_H__
#define __ELEPHANT_H__

#include "Piece.h"

template <typename MoveDirection>
class Elephant : public Piece
{
public:

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		GenerateMovesLeftForward(a_currentPos, a_board, a_outMoves);
		GenerateMovesRightForward(a_currentPos, a_board, a_outMoves);
		GenerateMovesLeftBackward(a_currentPos, a_board, a_outMoves);
		GenerateMovesRightBackward(a_currentPos, a_board, a_outMoves);
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        GenerateCaptureMovesLeftForward(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesRightForward(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesLeftBackward(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesRightBackward(a_currentPos, a_board, a_outMoves);
    }

private:

	void GenerateMovesLeftForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		Pos posLeftForward = MoveDirection::MoveLeft(MoveDirection::MoveForward(a_currentPos));

		if (a_board.IsEmpty(posLeftForward))
		{
			Pos posLeftForwardCorner = MoveDirection::MoveLeft(MoveDirection::MoveForward(posLeftForward));

			if (!MoveDirection::IsEnemyTerritory(posLeftForwardCorner))
			{
				if (a_board.IsEmpty(posLeftForwardCorner))
				{
					a_outMoves.AppendNonTakeMove(a_currentPos, posLeftForwardCorner);
				}
				else if (MoveDirection::IsEnemy(a_board[posLeftForwardCorner]))
				{
					a_outMoves.AppendTakeMove(a_currentPos, posLeftForwardCorner);
				}
			}
		}
	}

    void GenerateCaptureMovesLeftForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        Pos posLeftForward = MoveDirection::MoveLeft(MoveDirection::MoveForward(a_currentPos));

        if (a_board.IsEmpty(posLeftForward))
        {
            Pos posLeftForwardCorner = MoveDirection::MoveLeft(MoveDirection::MoveForward(posLeftForward));

            if (!MoveDirection::IsEnemyTerritory(posLeftForwardCorner))
            {
                if (MoveDirection::IsEnemy(a_board[posLeftForwardCorner]))
                {
                    a_outMoves.AppendTakeMove(a_currentPos, posLeftForwardCorner);
                }
            }
        }
    }

	void GenerateMovesRightForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		Pos posRightForward = MoveDirection::MoveRight(MoveDirection::MoveForward(a_currentPos));

		if (a_board.IsEmpty(posRightForward))
		{
			Pos posRightForwardCorner = MoveDirection::MoveRight(MoveDirection::MoveForward(posRightForward));

			if (!MoveDirection::IsEnemyTerritory(posRightForwardCorner))
			{
				if (a_board.IsEmpty(posRightForwardCorner))
				{
					a_outMoves.AppendNonTakeMove(a_currentPos, posRightForwardCorner);
				}
				else if (MoveDirection::IsEnemy(a_board[posRightForwardCorner]))
				{
					a_outMoves.AppendTakeMove(a_currentPos, posRightForwardCorner);
				}
			}
		}
	}

    void GenerateCaptureMovesRightForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        Pos posRightForward = MoveDirection::MoveRight(MoveDirection::MoveForward(a_currentPos));

        if (a_board.IsEmpty(posRightForward))
        {
            Pos posRightForwardCorner = MoveDirection::MoveRight(MoveDirection::MoveForward(posRightForward));

            if (!MoveDirection::IsEnemyTerritory(posRightForwardCorner))
            {
                if (MoveDirection::IsEnemy(a_board[posRightForwardCorner]))
                {
                    a_outMoves.AppendTakeMove(a_currentPos, posRightForwardCorner);
                }
            }
        }
    }

	void GenerateMovesLeftBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		Pos posLeftBackward = MoveDirection::MoveLeft(MoveDirection::MoveBackward(a_currentPos));

		if (a_board.IsEmpty(posLeftBackward))
		{
			Pos posLeftBackwardCorner = MoveDirection::MoveLeft(MoveDirection::MoveBackward(posLeftBackward));

			if (!MoveDirection::IsEnemyTerritory(posLeftBackwardCorner))
			{
				if (a_board.IsEmpty(posLeftBackwardCorner))
				{
					a_outMoves.AppendNonTakeMove(a_currentPos, posLeftBackwardCorner);
				}
				else if (MoveDirection::IsEnemy(a_board[posLeftBackwardCorner]))
				{
					a_outMoves.AppendTakeMove(a_currentPos, posLeftBackwardCorner);
				}
			}
		}
	}

    void GenerateCaptureMovesLeftBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        Pos posLeftBackward = MoveDirection::MoveLeft(MoveDirection::MoveBackward(a_currentPos));

        if (a_board.IsEmpty(posLeftBackward))
        {
            Pos posLeftBackwardCorner = MoveDirection::MoveLeft(MoveDirection::MoveBackward(posLeftBackward));

            if (!MoveDirection::IsEnemyTerritory(posLeftBackwardCorner))
            {
                if (MoveDirection::IsEnemy(a_board[posLeftBackwardCorner]))
                {
                    a_outMoves.AppendTakeMove(a_currentPos, posLeftBackwardCorner);
                }
            }
        }
    }

	void GenerateMovesRightBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		Pos posRightBackward = MoveDirection::MoveRight(MoveDirection::MoveBackward(a_currentPos));

		if (a_board.IsEmpty(posRightBackward))
		{
			Pos posRightBackwardCorner = MoveDirection::MoveRight(MoveDirection::MoveBackward(posRightBackward));

			if (!MoveDirection::IsEnemyTerritory(posRightBackwardCorner))
			{
				if (a_board.IsEmpty(posRightBackwardCorner))
				{
					a_outMoves.AppendNonTakeMove(a_currentPos, posRightBackwardCorner);
				}
				else if (MoveDirection::IsEnemy(a_board[posRightBackwardCorner]))
				{
					a_outMoves.AppendTakeMove(a_currentPos, posRightBackwardCorner);
				}
			}
		}
	}

    void GenerateCaptureMovesRightBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        Pos posRightBackward = MoveDirection::MoveRight(MoveDirection::MoveBackward(a_currentPos));

        if (a_board.IsEmpty(posRightBackward))
        {
            Pos posRightBackwardCorner = MoveDirection::MoveRight(MoveDirection::MoveBackward(posRightBackward));

            if (!MoveDirection::IsEnemyTerritory(posRightBackwardCorner))
            {
                if (MoveDirection::IsEnemy(a_board[posRightBackwardCorner]))
                {
                    a_outMoves.AppendTakeMove(a_currentPos, posRightBackwardCorner);
                }
            }
        }
    }
};

#endif // #ifndef __ELEPHANT_H__