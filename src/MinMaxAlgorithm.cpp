#include "Board.h"
#include "Common.h"
#include "Evaluator.h"
#include "MoveGenerator.h"
#include "MinMaxAlgorithm.h"

int32 MinMaxAlgorithm::Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    if (a_depthRemain <= 0)
    {
        return a_evaluator.Evaluate(a_board);
    }

    if (a_turn == RED_TURN)
    {
        return DoSearchRed(a_turn, a_depthRemain, a_board, a_evaluator, a_countNodes);
    }
    else
    {
        return DoSearchBlk(a_turn, a_depthRemain, a_board, a_evaluator, a_countNodes);
    }
}

int32 MinMaxAlgorithm::DoSearchRed(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    ++a_countNodes;

    if (a_depthRemain <= 0)
    {
        return a_evaluator.GetScore();
    }

    int32 scoreMax = -INFINITE;
    
    MoveGenerator *moveGenerator = GetMoveGeneratorAtDepth(m_currentDepth);
    const uint8 countMoves = moveGenerator->GenerateRedMoves(a_board);

    for (uint8 i = 0; i < countMoves; ++i)
    {
        const MovePos *move = moveGenerator->GetMove(i);

        if (!move)
        {
            break;
        }

        a_evaluator.ChangeScoreByMovePiece(m_currentDepth, a_board, move->from, move->to);
        a_board.Move(m_currentDepth, move->from, move->to);
        
        ++m_currentDepth;
        int32 score = DoSearchBlk(-a_turn, a_depthRemain - 1, a_board, a_evaluator, a_countNodes);
        --m_currentDepth;

        if (score > scoreMax)
        {
            scoreMax = score;
            SetBestMoveAtDepth(m_currentDepth, *move);
        }

        a_board.UndoMove(m_currentDepth, move->from, move->to);
        a_evaluator.ChangeScoreByUndoMove(m_currentDepth);
    }

    if (scoreMax == -INFINITE)
    {
        printf("No best Move!! Moves = %d\n", countMoves);
    }

    return scoreMax;
}

int32 MinMaxAlgorithm::DoSearchBlk(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    ++a_countNodes;

    if (a_depthRemain <= 0)
    {
        return a_evaluator.GetScore();
    }

    int32 scoreMin = INFINITE;

    MoveGenerator *moveGenerator = GetMoveGeneratorAtDepth(m_currentDepth);
    const uint8 countMoves = moveGenerator->GenerateBlkMoves(a_board);

    for (uint8 i = 0; i < countMoves; ++i)
    {
        const MovePos *move = moveGenerator->GetMove(i);

        if (!move)
        {
            break;
        }

        a_evaluator.ChangeScoreByMovePiece(m_currentDepth, a_board, move->from, move->to);
        a_board.Move(m_currentDepth, move->from, move->to);

        ++m_currentDepth;
        int32 score = DoSearchRed(-a_turn, a_depthRemain - 1, a_board, a_evaluator, a_countNodes);
        --m_currentDepth;

        if (score < scoreMin)
        {
            scoreMin = score;
            SetBestMoveAtDepth(m_currentDepth, *move);
        }

        a_board.UndoMove(m_currentDepth, move->from, move->to);
        a_evaluator.ChangeScoreByUndoMove(m_currentDepth);
    }

    return scoreMin;
}