#include <cstring>
#include <cassert>
#include "Moves.h"

namespace
{
	const uint8 DEFAULT_QUEUE_BEGIN_POS = 64;
}

Moves::Moves()
	:
m_countMoves(0),
m_head(DEFAULT_QUEUE_BEGIN_POS),
m_tail(DEFAULT_QUEUE_BEGIN_POS)
{
	memset(m_moves, 0, sizeof(MovePos) * MAX_MOVES);
}

void Moves::AppendNonTakeMove(Pos a_from, Pos a_to)
{
	m_moves[m_tail].from = a_from;
	m_moves[m_tail].to = a_to;

	++m_tail;

	assert(m_tail < MAX_MOVES);

	++m_countMoves;
}

void Moves::AppendTakeMove(Pos a_from, Pos a_to)
{
	assert(m_head > 0);

	--m_head;
	
	m_moves[m_head].from = a_from;
	m_moves[m_head].to = a_to;

	++m_countMoves;
}

void Moves::Clear()
{
	m_countMoves = 0;
	m_head = DEFAULT_QUEUE_BEGIN_POS;
	m_tail = DEFAULT_QUEUE_BEGIN_POS;
}

uint8 Moves::Count() const
{
	return m_countMoves;
}

const MovePos *Moves::GetMove(uint8 a_index) const
{
	if (a_index >= m_countMoves)
	{
		return 0;
	}

	return &m_moves[a_index + m_head];
}