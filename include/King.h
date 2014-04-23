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

        // 因為其他棋子移動，造成王見王的局面，為了簡化判斷，不在其他棋子移動時檢查，
        // 視為可以用己方主將直接吃掉對方的王
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

        // 因為其他棋子移動，造成王見王的局面，為了簡化判斷，不在其他棋子移動時檢查，
        // 視為可以用己方主將直接吃掉對方的王
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