#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#include <vector>
#include <cassert>
#include "Types.h"

class Board;
class Evaluator;
class MoveGenerator;
class TranspositionTable;

typedef std::vector<MovePos> BestMoves;
typedef std::vector<uint64> BoardLog;

class SearchAlgorithm
{
public:

    SearchAlgorithm();
    virtual ~SearchAlgorithm();

    int32 BeginSearch(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);

    const BestMoves &GetBestMoves() const
    {
        return m_bestMoves;
    }

protected:

    virtual int32 Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes) = 0;

    MoveGenerator *GetMoveGeneratorAtDepth(uint32 a_depth);
    void SetBestMoveAtDepth(uint32 a_depth, const MovePos &a_movePos);

    TranspositionTable *GetTranspositionTable() const
    {
        return m_transpositionTable;
    }

    uint64 GetBoardLog(uint32 a_index) const
    {
        assert(a_index < m_boardLog.size());

        if (a_index < m_boardLog.size())
        {
            return m_boardLog[a_index];
        }
        else
        {
            return 0;
        }
    }

    uint16 GetCurrentPlay() const
    {
        return m_currentPlay;
    }

    uint32 m_currentDepth;

private:

    typedef std::vector<MoveGenerator *> MoveGenerators;
    MoveGenerators m_moveGenerators;

    uint16 m_currentPlay;
    BestMoves m_bestMoves;
    BoardLog m_boardLog;
    TranspositionTable *m_transpositionTable;
};

#endif // #ifndef __SEARCH_ALGORITHM_H__