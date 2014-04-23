#ifndef __ROOK_H__
#define __ROOK_H__

#include "Piece.h"

template <typename MoveDirection>
class Rook : public Piece
{
public:

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		GenerateMovesForward(a_currentPos, a_board, a_outMoves);
		GenerateMovesBackward(a_currentPos, a_board, a_outMoves);
		GenerateMovesLeft(a_currentPos, a_board, a_outMoves);
		GenerateMovesRight(a_currentPos, a_board, a_outMoves);
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        GenerateCaptureMovesForward(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesBackward(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesLeft(a_currentPos, a_board, a_outMoves);
        GenerateCaptureMovesRight(a_currentPos, a_board, a_outMoves);
    }

private:

	void GenerateMovesForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
	{
		Pos pos = MoveDirection::MoveForward(a_currentPos);

		for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveForward(pos))
		{
			a_outMoves.AppendNonTakeMove(a_currentPos, pos);
		}

		if (MoveDirection::IsEnemy(a_board[pos]))
		{
			a_outMoves.AppendTakeMove(a_currentPos, pos);
		}
	}

    void GenerateCaptureMovesForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
    {
        Pos pos = MoveDirection::MoveForward(a_currentPos);

        for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveForward(pos))
        {
        }

        if (MoveDirection::IsEnemy(a_board[pos]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, pos);
        }
    }

	void GenerateMovesBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
	{
		Pos pos = MoveDirection::MoveBackward(a_currentPos);

		for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveBackward(pos))
		{
			a_outMoves.AppendNonTakeMove(a_currentPos, pos);
		}

		if (MoveDirection::IsEnemy(a_board[pos]))
		{
			a_outMoves.AppendTakeMove(a_currentPos, pos);
		}
	}

    void GenerateCaptureMovesBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
    {
        Pos pos = MoveDirection::MoveBackward(a_currentPos);

        for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveBackward(pos))
        {
        }

        if (MoveDirection::IsEnemy(a_board[pos]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, pos);
        }
    }

	void GenerateMovesLeft(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
	{
		Pos pos = MoveDirection::MoveLeft(a_currentPos);

		for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveLeft(pos))
		{
			a_outMoves.AppendNonTakeMove(a_currentPos, pos);
		}

		if (MoveDirection::IsEnemy(a_board[pos]))
		{
			a_outMoves.AppendTakeMove(a_currentPos, pos);
		}
	}

    void GenerateCaptureMovesLeft(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
    {
        Pos pos = MoveDirection::MoveLeft(a_currentPos);

        for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveLeft(pos))
        {
        }

        if (MoveDirection::IsEnemy(a_board[pos]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, pos);
        }
    }

	void GenerateMovesRight(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
	{
		Pos pos = MoveDirection::MoveRight(a_currentPos);

		for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveRight(pos))
		{
			a_outMoves.AppendNonTakeMove(a_currentPos, pos);
		}

		if (MoveDirection::IsEnemy(a_board[pos]))
		{
			a_outMoves.AppendTakeMove(a_currentPos, pos);
		}
	}

    void GenerateCaptureMovesRight(Pos a_currentPos, const Board &a_board, Moves &a_outMoves) const
    {
        Pos pos = MoveDirection::MoveRight(a_currentPos);

        for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveRight(pos))
        {
        }

        if (MoveDirection::IsEnemy(a_board[pos]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, pos);
        }
    }
};

#endif // #ifndef __ROOK_H__