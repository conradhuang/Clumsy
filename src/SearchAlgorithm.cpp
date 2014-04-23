#include "Common.h"
#include "Evaluator.h"
#include "MoveGenerator.h"
#include "SearchAlgorithm.h"
#include "Board.h"
#include "TranspositionTable.h"

SearchAlgorithm::SearchAlgorithm()
    :
m_currentPlay(0),
m_currentDepth(0)
{
    //m_moveGenerators.resize(MAX_SEARCH_DEPTH);
    //m_bestMoves.resize(MAX_SEARCH_DEPTH);
    m_transpositionTable = new TranspositionTable;
}

SearchAlgorithm::~SearchAlgorithm()
{
    MoveGenerators::const_iterator iter = m_moveGenerators.begin();

    for ( ; iter != m_moveGenerators.end(); ++iter)
    {
        delete (*iter);
    }

    m_moveGenerators.clear();

    delete m_transpositionTable;
    m_transpositionTable = 0;
}

int32 SearchAlgorithm::BeginSearch(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes)
{
    m_bestMoves.clear();
    m_bestMoves.resize(MAX_SEARCH_DEPTH);

    a_board.ClearTakenChesses();
    a_evaluator.Evaluate(a_board);
    m_transpositionTable->InitByBoard(a_turn, a_board);

    m_currentDepth = 0;

    int32 score = Search(a_turn, a_depthRemain, a_board, a_evaluator, a_countNodes);

    if (!GetBestMoves().empty())
    {
        MovePos bestMove = *(GetBestMoves().begin());
        GetTranspositionTable()->ChangeKeyByMoving(a_board.GetTypeAt(bestMove.from), bestMove.from, a_board.GetTypeAt(bestMove.to), bestMove.to);
        m_boardLog.push_back(GetTranspositionTable()->GetCurrentKey());
        GetTranspositionTable()->ChangeKeyByMoving(a_board.GetTypeAt(bestMove.from), bestMove.from, a_board.GetTypeAt(bestMove.to), bestMove.to);
    }

    ++m_currentPlay;

    return score;
}

MoveGenerator *SearchAlgorithm::GetMoveGeneratorAtDepth(uint32 a_depth)
{
    if (a_depth >= m_moveGenerators.size())
    {
        m_moveGenerators.resize(a_depth + 1);
    }
    
    if (!m_moveGenerators[a_depth])
    {
        m_moveGenerators[a_depth] = new MoveGenerator;
    }

    return m_moveGenerators[a_depth];
}

void SearchAlgorithm::SetBestMoveAtDepth(uint32 a_depth, const MovePos &a_movePos)
{
    if (a_depth >= m_bestMoves.size())
    {
        m_bestMoves.resize(a_depth + 1);
    }

    m_bestMoves[a_depth] = a_movePos;
}