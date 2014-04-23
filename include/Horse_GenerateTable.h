#ifndef __HORSE_H__
#define __HORSE_H__

#include "Piece.h"

template <typename MoveDirection>
class Horse : public Piece
{
public:

    Horse()
        :
    m_legIndex(0)
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            memset(m_horseLeg[i], 0, sizeof(Pos) * 4);
            memset(m_horsePos[i], 0, sizeof(Pos) * 8);
        }
    }

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
        m_legIndex = 0;

		GenerateMovesForward(a_currentPos, a_board, a_outMoves);
		GenerateMovesBackward(a_currentPos, a_board, a_outMoves);
		GenerateMovesLeft(a_currentPos, a_board, a_outMoves);
		GenerateMovesRight(a_currentPos, a_board, a_outMoves);
	}

    void PrintHorseLeg()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            printf("%3d, %3d, %3d, %3d, // %3d\n", m_horseLeg[i][0], m_horseLeg[i][1], m_horseLeg[i][2], m_horseLeg[i][3], i);
        }
    }

    void PrintHorsePos()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                printf("%3d,", m_horsePos[i][j]);

                if (j != 7)
                {
                    printf(" ");
                }
            }

            printf("// %3d\n", i);
        }
    }

private:

    int m_legIndex;
    Pos m_horseLeg[BOARD_SIZE][4];
    Pos m_horsePos[BOARD_SIZE][8];

	void GenerateMovesForward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		const Pos posForward = MoveDirection::MoveForward(a_currentPos);

		if (a_board.IsBoundary(posForward))
		{
            return;
        }

        m_horseLeg[a_currentPos][m_legIndex] = posForward;

        const Pos posForwardTwice = MoveDirection::MoveForward(posForward);

        if (a_board.IsBoundary(posForwardTwice))
        {
            return;
        }

        int begin = m_legIndex * 2;

        if (!a_board.IsBoundary(MoveDirection::MoveLeft(posForwardTwice)))
        {
            m_horsePos[a_currentPos][begin++] = MoveDirection::MoveLeft(posForwardTwice);
        }
        
        if (a_board.IsEmpty(MoveDirection::MoveLeft(posForwardTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveLeft(posForwardTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveLeft(posForwardTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveLeft(posForwardTwice));
        }

        if (!a_board.IsBoundary(MoveDirection::MoveRight(posForwardTwice)))
        {
            m_horsePos[a_currentPos][begin] = MoveDirection::MoveRight(posForwardTwice);
        }

        if (a_board.IsEmpty(MoveDirection::MoveRight(posForwardTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveRight(posForwardTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveRight(posForwardTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveRight(posForwardTwice));
        }

        ++m_legIndex;
	}

	void GenerateMovesBackward(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		const Pos posBackward = MoveDirection::MoveBackward(a_currentPos);

        if (a_board.IsBoundary(posBackward))
        {
            return;
        }

        m_horseLeg[a_currentPos][m_legIndex] = posBackward;

        const Pos posBackwardTwice = MoveDirection::MoveBackward(posBackward);

        if (a_board.IsBoundary(posBackwardTwice))
        {
            return;
        }

        int begin = m_legIndex * 2;

        if (!a_board.IsBoundary(MoveDirection::MoveLeft(posBackwardTwice)))
        {
            m_horsePos[a_currentPos][begin++] = MoveDirection::MoveLeft(posBackwardTwice);
        }
        
        if (a_board.IsEmpty(MoveDirection::MoveLeft(posBackwardTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveLeft(posBackwardTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveLeft(posBackwardTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveLeft(posBackwardTwice));
        }

        if (!a_board.IsBoundary(MoveDirection::MoveRight(posBackwardTwice)))
        {
            m_horsePos[a_currentPos][begin] = MoveDirection::MoveRight(posBackwardTwice);
        }

        if (a_board.IsEmpty(MoveDirection::MoveRight(posBackwardTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveRight(posBackwardTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveRight(posBackwardTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveRight(posBackwardTwice));
        }

        ++m_legIndex;
	}

	void GenerateMovesLeft(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		const Pos posLeft = MoveDirection::MoveLeft(a_currentPos);

        if (a_board.IsBoundary(posLeft))
        {
            return;
        }

        m_horseLeg[a_currentPos][m_legIndex] = posLeft;

        const Pos posLeftTwice = MoveDirection::MoveLeft(posLeft);

        if (a_board.IsBoundary(posLeftTwice))
        {
            return;
        }

        int begin = m_legIndex * 2;

        if (!a_board.IsBoundary(MoveDirection::MoveForward(posLeftTwice)))
        {
            m_horsePos[a_currentPos][begin++] = MoveDirection::MoveForward(posLeftTwice);
        }

        if (a_board.IsEmpty(MoveDirection::MoveForward(posLeftTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveForward(posLeftTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveForward(posLeftTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveForward(posLeftTwice));
        }

        if (!a_board.IsBoundary(MoveDirection::MoveBackward(posLeftTwice)))
        {
            m_horsePos[a_currentPos][begin++] = MoveDirection::MoveBackward(posLeftTwice);
        }
        
        if (a_board.IsEmpty(MoveDirection::MoveBackward(posLeftTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveBackward(posLeftTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveBackward(posLeftTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveBackward(posLeftTwice));
        }

        ++m_legIndex;
	}

	void GenerateMovesRight(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		const Pos posRight = MoveDirection::MoveRight(a_currentPos);

        if (a_board.IsBoundary(posRight))
        {
            return;
        }

        m_horseLeg[a_currentPos][m_legIndex] = posRight;

        const Pos posRightTwice = MoveDirection::MoveRight(posRight);

        if (a_board.IsBoundary(posRightTwice))
        {
            return;
        }

        int begin = m_legIndex * 2;

        if (!a_board.IsBoundary(MoveDirection::MoveForward(posRightTwice)))
        {
            m_horsePos[a_currentPos][begin++] = MoveDirection::MoveForward(posRightTwice);
        }

        if (a_board.IsEmpty(MoveDirection::MoveForward(posRightTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveForward(posRightTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveForward(posRightTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveForward(posRightTwice));
        }

        if (!a_board.IsBoundary(MoveDirection::MoveBackward(posRightTwice)))
        {
            m_horsePos[a_currentPos][begin] = MoveDirection::MoveBackward(posRightTwice);
        }

        if (a_board.IsEmpty(MoveDirection::MoveBackward(posRightTwice)))
        {
            a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::MoveBackward(posRightTwice));
        }
        else if (MoveDirection::IsEnemy(a_board[MoveDirection::MoveBackward(posRightTwice)]))
        {
            a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::MoveBackward(posRightTwice));
        }

        ++m_legIndex;
	}
};

#endif // #ifndef __HORSE_H__