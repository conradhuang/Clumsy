#ifndef __KING_H__
#define __KING_H__

#include "Piece.h"
#include "Types.h"
#include "Common.h"

template <typename MoveDirection>
class King : public Piece
{
public:

    King()
    {
    }

	virtual void GenerateMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
	{
		for (int32 i = 0; MoveDirection::s_kingPos[a_currentPos][i]; ++i)
        {
            if (a_board.IsEmpty(MoveDirection::s_kingPos[a_currentPos][i]))
            {
                a_outMoves.AppendNonTakeMove(a_currentPos, MoveDirection::s_kingPos[a_currentPos][i]);
            }
            else if (MoveDirection::IsEnemy(a_board[MoveDirection::s_kingPos[a_currentPos][i]]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::s_kingPos[a_currentPos][i]);
            }
        }

        // �]����L�Ѥl���ʡA�y���������������A���F²�ƧP�_�A���b��L�Ѥl���ʮ��ˬd�A
        // �����i�H�Τv��D�N�����Y����誺��
        if (IsKingFaceKing(a_board, a_currentPos))
        {
            a_outMoves.AppendTakeMove(a_currentPos, a_board.GetPos(MoveDirection::EnemyKing()));
        }
	}

    virtual void GenerateCaptureMoves(Pos a_currentPos, const Board &a_board, Moves &a_outMoves)
    {
        for (int32 i = 0; MoveDirection::s_kingPos[a_currentPos][i]; ++i)
        {
            if (MoveDirection::IsEnemy(a_board[MoveDirection::s_kingPos[a_currentPos][i]]))
            {
                a_outMoves.AppendTakeMove(a_currentPos, MoveDirection::s_kingPos[a_currentPos][i]);
            }
        }

        // �]����L�Ѥl���ʡA�y���������������A���F²�ƧP�_�A���b��L�Ѥl���ʮ��ˬd�A
        // �����i�H�Τv��D�N�����Y����誺��
        if (IsKingFaceKing(a_board, a_currentPos))
        {
            a_outMoves.AppendTakeMove(a_currentPos, a_board.GetPos(MoveDirection::EnemyKing()));
        }
    }

    bool IsKingFaceKing(const Board &a_board, Pos a_posToMove) const
    {
        Pos pos = MoveDirection::MoveForward(a_posToMove);

        for (; a_board.IsEmpty(pos); pos = MoveDirection::MoveForward(pos))
        {
        }

        return MoveDirection::IsEnemyKing(a_board[pos]);
    }
};

#endif // #ifndef __KING_H__