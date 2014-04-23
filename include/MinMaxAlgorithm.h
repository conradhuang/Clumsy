#ifndef __MIN_MAX_ALGORITHM_H__
#define __MIN_MAX_ALGORITHM_H__

#include "SearchAlgorithm.h"
#include "Types.h"

class MinMaxAlgorithm : public SearchAlgorithm
{
public:

    virtual int32 Search(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);

private:

    int32 DoSearchRed(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);
    int32 DoSearchBlk(int32 a_turn, uint32 a_depthRemain, Board &a_board, Evaluator &a_evaluator, uint32 &a_countNodes);
};

#endif // #ifndef __MIN_MAX_ALGORITHM_H__