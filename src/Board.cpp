#include <cstring>
#include "Board.h"

bool Board::s_isBoundary[BOARD_SIZE] = {false};
bool Board::s_isRedTerritory[BOARD_SIZE] = {false};
bool Board::s_isBlkTerritory[BOARD_SIZE] = {false};

const Pos Board::s_beginPos[MAX_CHESS] = 
{
	0,						 // NONE
	L41, L43, L45, L47, L49, // Black Pawn
	L32, L38,				 // Black Cannon
	L12, L18,				 // Black Horse
	L11, L19,				 // Black Rook
	L13, L17,				 // Black Elephant
	L14, L16,				 // Black Guard
	L15,					 // Black King
	0,						 // BOUNDARY
	L71, L73, L75, L77, L79, // Red Pawn
	L82, L88,				 // Red Cannon
	L102, L108,				 // Red Horse
	L101, L109,				 // Red Rook
	L103, L107,				 // Red Elephant
	L104, L106,				 // Red Guard
	L105					 // Red King
};

const ChessType Board::s_chessType[MAX_CHESS] = {
	EMPTY,				// NONE
	BP, BP, BP, BP, BP, // Black Pawn
	BC, BC,				// Black Cannon
	BH, BH,				// Black Horse
	BR, BR,				// Black Rook
	BE, BE,				// Black Elephant
	BG, BG,				// Black Guard
	BK,					// Black King
	BNDRY,				// BOUNDARY
	RP, RP, RP, RP, RP, // Red Pawn
	RC, RC,				// Red Cannon
	RH, RH,				// Red Horse
	RR, RR,				// Red Rook
	RE, RE,				// Red Elephant
	RG, RG,				// Red Guard
	RK,					// Red King
};

void Board::Init()
{
	for (int i = L0; i < L10; ++i)
	{
		s_isBoundary[i] = true;
		s_isBoundary[i + L110] = true;
	}

	for (int i = L10; i < L110; i += 10)
	{
		s_isBoundary[i] = true;
	}

	for (int i = L11; i < L60; ++i)
	{
		if (!s_isBoundary[i])
		{
			s_isBlkTerritory[i] = true;
		}
	}

	for (int i = L61; i < L110; ++i)
	{
		if (!s_isBoundary[i])
		{
			s_isRedTerritory[i] = true;
		}
	}
}

Board::Board()
{
	InitBoundary();

	memset(m_pcePos, 0, sizeof(Pos) * MAX_CHESS);
	memset(m_isDead, 0, sizeof(bool) * MAX_CHESS);

	InitPiece(BLK_PAWN_1, BLK_KING);
	InitPiece(RED_PAWN_1, RED_KING);
}

void Board::InitBoundary()
{
	memset(m_board, 0, sizeof(Chess) * BOARD_SIZE);

	for (int i = L0; i < L10; ++i)
	{
		m_board[i] = BOUNDARY;
		m_board[i + L110] = BOUNDARY;
	}

	for (int i = L10; i < L110; i += 10)
	{
		m_board[i] = BOUNDARY;
	}
}

void Board::Purge()
{
    InitBoundary();

    memset(m_pcePos, 0, sizeof(Pos) * MAX_CHESS);
    memset(m_isDead, 0, sizeof(bool) * MAX_CHESS);

    ClearTakenChesses();
}

void Board::InitPiece(Chess a_begin, Chess a_end)
{
	for (int i = a_begin; i <= a_end; ++i)
	{
		m_board[s_beginPos[i]] = static_cast<Chess>(i);
		m_pcePos[i] = s_beginPos[i];
	}
}

void Board::Move(uint32 a_depth, Pos a_from, Pos a_to)
{
	assert(m_board[a_from] != NONE);
	assert(m_board[a_from] != BOUNDARY);
    assert(m_board[a_to] != BOUNDARY);

	assert(!IsDead(m_board[a_from]));

	if (m_board[a_to] != NONE)
	{
		assert(!IsDead(m_board[a_to]));

		m_isDead[m_board[a_to]] = true;

        if (a_depth >= m_takenChess.size())
        {
            m_takenChess.resize(a_depth + 1);
        }

		m_takenChess[a_depth] = m_board[a_to];
	}

	m_board[a_to] = m_board[a_from];
	m_board[a_from] = NONE;

	m_pcePos[m_board[a_to]] = a_to;
}

void Board::UndoMove(uint32 a_depth, Pos a_from, Pos a_to)
{
	assert(m_board[a_from] == NONE);
	assert(m_board[a_to] != NONE);
	assert(m_board[a_to] != BOUNDARY);
	assert(!IsDead(m_board[a_to]));
    assert(a_depth < m_takenChess.size());

	m_board[a_from] = m_board[a_to];
	m_pcePos[m_board[a_from]] = a_from;

	if (m_takenChess[a_depth] != NONE)
	{
		m_board[a_to] = m_takenChess[a_depth];
		m_isDead[m_takenChess[a_depth]] = false;
		m_takenChess[a_depth] = NONE;
	}
	else
	{
		m_board[a_to] = NONE;
	}
}

void Board::ClearTakenChesses()
{
    m_takenChess.clear();
    m_takenChess.resize(MAX_SEARCH_DEPTH);
}