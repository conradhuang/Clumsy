#ifndef __NEGAMAX_ALGORITHM_H__
#define __NEGAMAX_ALGORITHM_H__

#include "SearchAlgorithm.h"
#include "Types.h"

class NegamaxAlgorithm : public SearchAlgorithm
{
public:

    virtual int32 Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);

private:

    int32 DoSearch(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);
};

#endif // #ifndef __NEGAMAX_ALGORITHM_H__