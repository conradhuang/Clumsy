#ifndef __MOVES_H__
#define __MOVES_H__

#include "Types.h"

class Moves
{
public:

	Moves();

	void AppendNonTakeMove(Pos a_from, Pos a_to);
	void AppendTakeMove(Pos a_from, Pos a_to);
	void Clear();
	uint8 Count() const;
	const MovePos *GetMove(uint8 a_index) const;

private:

	enum
	{
		MAX_MOVES = 256
	};

	uint8 m_countMoves;
	uint8 m_head;
	uint8 m_tail;
	MovePos m_moves[MAX_MOVES];
};

#endif // ifndef __MOVES_H__