#ifndef __PAWN_H__
#define __PAWN_H__

#include "Piece.h"

template <typename MoveDirection>
class Pawn : public Piece
{
public:

	Pawn()
	{
	}

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		const Pos posForward = MoveDirection::MoveForward(a_currentPos);
        const Chess chess = a_board[posForward];

		if (a_board.IsEmpty(chess))
		{
            assert(a_board[posForward] != BOUNDARY);

			a_outMoves.AppendNonTakeMove(a_currentPos, posForward);
		}
        else if (MoveDirection::IsEnemy(chess))
        {
            assert(a_board[posForward] != BOUNDARY);

            a_outMoves.AppendTakeMove(a_currentPos, posForward);
        }

		if (MoveDirection::IsEnemyTerritory(a_currentPos))
		{
			const Pos posLeft = MoveDirection::MoveLeft(a_currentPos);

			if (a_board.IsEmpty(posLeft))
			{
                assert(a_board[posLeft] != BOUNDARY);

				a_outMoves.AppendNonTakeMove(a_currentPos, posLeft);
			}
            else if (MoveDirection::IsEnemy(a_board[posLeft]))
            {
                assert(a_board[posLeft] != BOUNDARY);

                a_outMoves.AppendTakeMove(a_currentPos, posLeft);
            }

			const Pos posRight = MoveDirection::MoveRight(a_currentPos);

			if (a_board.IsEmpty(posRight))
			{
                assert(a_board[posRight] != BOUNDARY);

				a_outMoves.AppendNonTakeMove(a_currentPos, posRight);
			}
            else if (MoveDirection::IsEnemy(a_board[posRight]))
            {
                assert(a_board[posRight] != BOUNDARY);

                a_outMoves.AppendTakeMove(a_currentPos, posRight);
            }
		}
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        const Pos posForward = MoveDirection::MoveForward(a_currentPos);

        if (MoveDirection::IsEnemy(a_board[posForward]))
        {
            assert(a_board[posForward] != BOUNDARY);

            a_outMoves.AppendTakeMove(a_currentPos, posForward);
        }

        if (MoveDirection::IsEnemyTerritory(a_currentPos))
        {
            const Pos posLeft = MoveDirection::MoveLeft(a_currentPos);

            if (MoveDirection::IsEnemy(a_board[posLeft]))
            {
                assert(a_board[posLeft] != BOUNDARY);

                a_outMoves.AppendTakeMove(a_currentPos, posLeft);
            }

            const Pos posRight = MoveDirection::MoveRight(a_currentPos);

            if (MoveDirection::IsEnemy(a_board[posRight]))
            {
                assert(a_board[posRight] != BOUNDARY);

                a_outMoves.AppendTakeMove(a_currentPos, posRight);
            }
        }
    }
};

#endif // ifndef __PAWN_H__