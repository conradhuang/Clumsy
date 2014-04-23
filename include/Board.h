#ifndef __BOARD_H__
#define __BOARD_H__

#include <cassert>
#include <vector>
#include "Common.h"
#include "Types.h"

enum Location
{
 	  L0,   L1,   L2,   L3,   L4,   L5,   L6,   L7,   L8,   L9, // BOUNDARY
 	 L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,
	 L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,
	 L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,
	 L40,  L41,  L42,  L43,  L44,  L45,  L46,  L47,  L48,  L49,
	 L50,  L51,  L52,  L53,  L54,  L55,  L56,  L57,  L58,  L59, // River
	 L60,  L61,  L62,  L63,  L64,  L65,  L66,  L67,  L68,  L69, // River
	 L70,  L71,  L72,  L73,  L74,  L75,  L76,  L77,  L78,  L79,
	 L80,  L81,  L82,  L83,  L84,  L85,  L86,  L87,  L88,  L89,
	 L90,  L91,  L92,  L93,  L94,  L95,  L96,  L97,  L98,  L99,
	L100, L101, L102, L103, L104, L105, L106, L107, L108, L109, // End Of Board
	L110, L111, L112, L113, L114, L115, L116, L117, L118, L119  // BOUNDARY
};

class Board
{
public:

	Board();

    void Purge();

	void Move(uint32 a_depth, Pos a_from, Pos a_to);
	void UndoMove(uint32 a_depth, Pos a_from, Pos a_to);

	Chess operator[](const int a_pos) const
	{
		assert(a_pos >= L0 && a_pos < BOARD_SIZE);

		return m_board[a_pos];
	}

    void SetPos(const Chess a_chess, const Pos a_pos)
    {
        assert(a_pos >= L0 && a_pos < BOARD_SIZE);

        m_board[a_pos] = a_chess;
        m_pcePos[a_chess] = a_pos;
    }

    void SetDead(const Chess a_chess)
    {
        m_isDead[a_chess] = true;
    }

	Pos GetPos(Chess a_chess) const
	{
		assert(a_chess > NONE);
		assert(a_chess != BOUNDARY);
		assert(a_chess < MAX_CHESS);

		return m_pcePos[a_chess];
	}

	bool IsDead(Chess a_chess) const
	{
		assert(a_chess < MAX_CHESS);
		assert(a_chess != NONE);
		assert(a_chess != BOUNDARY);

		return m_isDead[a_chess];
	}

	bool IsEmpty(Pos a_pos) const
	{
		assert(a_pos >= L0);
		assert(a_pos < BOARD_SIZE);

		return m_board[a_pos] == NONE;
	}

    void ClearTakenChesses();

	static void Init();

	static bool IsBoundary(Pos a_pos)
	{
		assert(a_pos >= L0 && a_pos < BOARD_SIZE);

		return s_isBoundary[a_pos];
	}

	static bool IsRedTerritory(Pos a_pos)
	{
		assert(a_pos >= L0 && a_pos < BOARD_SIZE);
		assert(!IsBoundary(a_pos));

		return s_isRedTerritory[a_pos];
	}

	static bool IsBlkTerritory(Pos a_pos)
	{
		assert(a_pos >= L0 && a_pos < BOARD_SIZE);
		assert(!IsBoundary(a_pos));

		return s_isBlkTerritory[a_pos];
	}

	static ChessType GetType(Chess a_chess)
	{
		assert(a_chess >= NONE);
		assert(a_chess < MAX_CHESS);

		return s_chessType[a_chess];
	}

    ChessType GetTypeAt(Pos a_pos)
    {
        assert(a_pos >= 0);
        assert(a_pos < BOARD_SIZE);
        assert(!IsBoundary(a_pos));

        return s_chessType[m_board[a_pos]];
    }

private:

	void InitBoundary();
	void InitPiece(Chess a_begin, Chess a_end);

	static const Pos s_beginPos[MAX_CHESS];
	static const ChessType s_chessType[MAX_CHESS];
	static bool s_isBoundary[BOARD_SIZE];
	static bool s_isRedTerritory[BOARD_SIZE];
	static bool s_isBlkTerritory[BOARD_SIZE];

	bool m_isDead[MAX_CHESS];
	
	Chess m_board[BOARD_SIZE];
	Pos m_pcePos[MAX_CHESS];

    typedef std::vector<Chess> TakenChesses;
    TakenChesses m_takenChess;
};

#endif // ifndef __BOARD_H__