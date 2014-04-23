#ifndef __ALPHA_BETA_ALGORITHM_H__
#define __ALPHA_BETA_ALGORITHM_H__

#include <vector>
#include "SearchAlgorithm.h"

class AlphaBetaAlgorithm : public SearchAlgorithm
{
public:

    virtual int32 Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);

private:

    int32 DoSearch(int32 a_turn, uint32 a_depthRemain, int32 a_alpha, int32 a_beta, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes, bool a_nullMove);
    bool IsBoardCyclic() const;
    bool IsRepeatMove() const;
    int32 QuiescenceSearch(int32 a_turn, int32 a_alpha, int32 a_beta, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);

    std::vector<uint64> m_boardHistory;
};

#endif // #ifndef __ALPHA_BETA_ALGORITHM_H__