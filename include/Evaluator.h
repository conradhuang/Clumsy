#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include <vector>
#include "Common.h"
#include "Types.h"

class Board;

class Evaluator
{
public:

	Evaluator();

	int32 Evaluate(const Board &a_board);

	int32 ChangeScoreByMovePiece(uint32 a_depth, const Board &a_board, Pos a_from, Pos a_to);
    int32 ChangeScoreByUndoMove(uint32 a_depth);

    int32 GetScore() const;

private:

	int32 m_score;

    typedef std::vector<int32> ScoreOfDepth;
    ScoreOfDepth m_scoreOfDepth;
};

#endif // #ifndef __EVALUATOR_H__