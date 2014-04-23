#include "AlphaBetaAlgorithm.h"
#include "Common.h"
#include "Board.h"
#include "Evaluator.h"
#include "MoveGenerator.h"
#include "TranspositionTable.h"
#include "Display.h"

uint32 g_countNullMovePrunned = 0;

int32 AlphaBetaAlgorithm::Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    m_boardHistory.clear();

    return DoSearch(a_turn, a_depthRemain, -INFINITE, INFINITE, a_board, a_evaluator, a_countNodes, true);
}

int32 AlphaBetaAlgorithm::DoSearch(int32 a_turn, uint32 a_depthRemain, int32 a_alpha, int32 a_beta, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes, bool a_nullMove)
{
    ++a_countNodes;

    if (a_depthRemain <= 0)
    {
        return a_turn * QuiescenceSearch(a_turn, a_alpha, a_beta, a_board, a_evaluator, a_countNodes);
    }

    if (a_board.IsDead(BLK_KING))
    {
        return a_turn * (INFINITE - m_currentDepth);
    }
    else if (a_board.IsDead(RED_KING))
    {
        return a_turn * (-INFINITE + m_currentDepth);
    }

    int32 scoreSaved = 0;
    MovePos bestMove;

    if (m_currentDepth != 0 && 
        a_depthRemain > 2 && 
        GetTranspositionTable()->IsExist(a_depthRemain, scoreSaved, bestMove))
    {
        if (scoreSaved >= a_beta)
        {
            return a_beta;
        }

        if (scoreSaved > a_alpha)
        {
            a_alpha = scoreSaved;
            SetBestMoveAtDepth(m_currentDepth, bestMove);
        }

        return a_alpha;
    }

    // TODO : don't use null-move if I'm checked
    if (a_nullMove && a_depthRemain > 2)
    {
        GetTranspositionTable()->ChangeKeyByNullMove();
        
        scoreSaved = -DoSearch(-a_turn, a_depthRemain - 2, -a_beta, -a_beta + 1, a_board, a_evaluator, a_countNodes, false);
        
        GetTranspositionTable()->ChangeKeyByNullMove();

        if (scoreSaved >= a_beta)
        {
            ++g_countNullMovePrunned;
            return a_beta;
        }
    }

    MoveGenerator *moveGenerator = GetMoveGeneratorAtDepth(m_currentDepth);
    const uint8 countMoves = (a_turn == RED_TURN) ? moveGenerator->GenerateRedMoves(a_board) : moveGenerator->GenerateBlkMoves(a_board);

    for (uint8 i = 0; i < countMoves; ++i)
    {
        const MovePos *move = moveGenerator->GetMove(i);

        if (!move)
        {
            break;
        }

        uint64 beforeKey = GetTranspositionTable()->GetCurrentKey();
        
        GetTranspositionTable()->ChangeKeyByMoving(a_board.GetTypeAt(move->from), move->from, a_board.GetTypeAt(move->to), move->to);

        uint32 currentDepth = m_currentDepth;

        if ((m_currentDepth == 0 && IsRepeatMove()) || 
            IsBoardCyclic())
        {
            if (a_turn * a_evaluator.GetScore() < 0)
            {
                GetTranspositionTable()->ChangeKeyByMoving(a_board.GetTypeAt(move->from), move->from, a_board.GetTypeAt(move->to), move->to);
                continue;
            }
        }

        m_boardHistory.push_back(beforeKey);

        a_evaluator.ChangeScoreByMovePiece(m_currentDepth, a_board, move->from, move->to);

        a_board.Move(m_currentDepth, move->from, move->to);

        ++m_currentDepth;
        int32 score = -DoSearch(-a_turn, a_depthRemain - 1, -a_beta, -a_alpha, a_board, a_evaluator, a_countNodes, a_nullMove);
        --m_currentDepth;

        a_board.UndoMove(m_currentDepth, move->from, move->to);
        uint64 afterKey = GetTranspositionTable()->ChangeKeyByMoving(a_board.GetTypeAt(move->from), move->from, a_board.GetTypeAt(move->to), move->to);
        assert(beforeKey == afterKey);
        
        m_boardHistory.pop_back();
        
        a_evaluator.ChangeScoreByUndoMove(m_currentDepth);

        if (score > a_alpha)
        {
            if (score >= a_beta)
            {
                return a_beta;
            }

            a_alpha = score;
            bestMove = *move;
            SetBestMoveAtDepth(m_currentDepth, *move);
        }
    }

    if (a_alpha == -INFINITE)
    {
        printf("No best Move!! Moves = %d\n", countMoves);
    }

    if (a_depthRemain > 2)
    {
        GetTranspositionTable()->Store(a_depthRemain, a_alpha, bestMove);
    }

    return a_alpha;
}

bool AlphaBetaAlgorithm::IsRepeatMove() const
{
    if (GetCurrentPlay() < 3)
    {
        return false;
    }

    uint16 currentPlay = GetCurrentPlay();

    while (currentPlay >= 4)
    {
        uint64 prevBoardHash = GetBoardLog(currentPlay - 4);

        assert(prevBoardHash != 0);

        if (!prevBoardHash)
        {
            return false;
        }

        if (prevBoardHash == GetTranspositionTable()->GetCurrentKey())
        {
            return true;
        }

        currentPlay -= 2;
    }
    
    return false;
}

bool AlphaBetaAlgorithm::IsBoardCyclic() const
{
    uint32 currentDepth = m_currentDepth;

    while (currentDepth >= 4)
    {
        assert(m_boardHistory.size() > 3);

        if (m_boardHistory[currentDepth - 4] == GetTranspositionTable()->GetCurrentKey())
        {
            return true;
        }

        currentDepth -= 2;
    }

    return false;
}

int32 AlphaBetaAlgorithm::QuiescenceSearch(int32 a_turn, int32 a_alpha, int32 a_beta, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    ++a_countNodes;

    if (a_evaluator.GetScore() > a_alpha)
    {
        if (a_evaluator.GetScore() >= a_beta)
        {
            // We must return a_evaluator.GetScore() here instead of a_beta!
            return a_evaluator.GetScore();
        }

        a_alpha = a_evaluator.GetScore();
    }

    if (a_board.IsDead(BLK_KING) || 
        a_board.IsDead(RED_KING))
    {
        return a_evaluator.GetScore();
    }

    MoveGenerator *moveGenerator = GetMoveGeneratorAtDepth(m_currentDepth);
    const uint8 countMoves = (a_turn == RED_TURN) ? moveGenerator->GenerateRedCaptureMoves(a_board) : moveGenerator->GenerateBlkCaptureMoves(a_board);

    for (uint8 i = 0; i < countMoves; ++i)
    {
        const MovePos *move = moveGenerator->GetMove(i);

        if (!move)
        {
            break;
        }

        assert(!a_board.IsEmpty(move->to));

        a_evaluator.ChangeScoreByMovePiece(m_currentDepth, a_board, move->from, move->to);
        a_board.Move(m_currentDepth, move->from, move->to);

        ++m_currentDepth;
        int32 score = -QuiescenceSearch(-a_turn, -a_beta, -a_alpha, a_board, a_evaluator, a_countNodes);
        --m_currentDepth;

        a_board.UndoMove(m_currentDepth, move->from, move->to);

        a_evaluator.ChangeScoreByUndoMove(m_currentDepth);

        if (score > a_alpha)
        {
            if (score >= a_beta)
            {
                return score;
            }

            a_alpha = score;
        }
    }

    return a_alpha;
}