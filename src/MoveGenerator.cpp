#include <cstring>
#include <ctime>
#include "Board.h"
#include "MoveDirectionBlack.h"
#include "MoveDirectionRed.h"
#include "MoveGenerator.h"
#include "Moves.h"
#include "Pawn.h"
#include "Cannon.h"
#include "Rook.h"
#include "Horse.h"
#include "Elephant.h"
#include "Guard.h"
#include "King.h"

Piece *MoveGenerator::s_generatorByType[MAX_CHESS_TYPE] = {0};
Piece *MoveGenerator::s_generatorByChess[MAX_CHESS] = {0};
uint64 MoveGenerator::s_clocksByChess[MAX_CHESS] = {0};

void MoveGenerator::Init()
{
	s_generatorByType[BP] = new Pawn<MoveDirectionBlack>;
	s_generatorByType[BC] = new Cannon<MoveDirectionBlack>;
	s_generatorByType[BR] = new Rook<MoveDirectionBlack>;
	s_generatorByType[BH] = new Horse<MoveDirectionBlack>;
	s_generatorByType[BE] = new Elephant<MoveDirectionBlack>;
	s_generatorByType[BG] = new Guard<MoveDirectionBlack>;
	s_generatorByType[BK] = new King<MoveDirectionBlack>;

	for (int i = BLK_PAWN_1; i <= BLK_KING; ++i)
	{
		s_generatorByChess[i] = s_generatorByType[Board::GetType(static_cast<Chess>(i))];
	}

	s_generatorByType[RP] = new Pawn<MoveDirectionRed>;
	s_generatorByType[RC] = new Cannon<MoveDirectionRed>;
	s_generatorByType[RR] = new Rook<MoveDirectionRed>;
	s_generatorByType[RH] = new Horse<MoveDirectionRed>;
	s_generatorByType[RE] = new Elephant<MoveDirectionRed>;
	s_generatorByType[RG] = new Guard<MoveDirectionRed>;
	s_generatorByType[RK] = new King<MoveDirectionRed>;

	for (int i = RED_PAWN_1; i <= RED_KING; ++i)
	{
		s_generatorByChess[i] = s_generatorByType[Board::GetType(static_cast<Chess>(i))];
	}
}

void MoveGenerator::Release()
{
	for (int i = 0; i < MAX_CHESS_TYPE; ++i)
	{
		delete s_generatorByType[i];
		s_generatorByType[i] = 0;
	}

	memset(s_generatorByChess, 0, sizeof(Piece *) * MAX_CHESS);
}

MoveGenerator::MoveGenerator()
{
	m_moves = new Moves;
}

MoveGenerator::~MoveGenerator()
{
	delete m_moves;
	m_moves = 0;
}

uint8 MoveGenerator::GenerateRedMoves(Board &a_board)
{
	m_moves->Clear();

	for (int currentChess = RED_PAWN_1; currentChess <= RED_KING; ++currentChess)
	{
		GenerateMoves(static_cast<Chess>(currentChess), a_board);
	}

	return m_moves->Count();
}

uint8 MoveGenerator::GenerateRedCaptureMoves(Board &a_board)
{
    m_moves->Clear();

    for (int currentChess = RED_PAWN_1; currentChess <= RED_KING; ++currentChess)
    {
        GenerateCaptureMoves(static_cast<Chess>(currentChess), a_board);
    }

    return m_moves->Count();
}

uint8 MoveGenerator::GenerateBlkMoves(Board &a_board)
{
	m_moves->Clear();

	for (int currentChess = BLK_PAWN_1; currentChess <= BLK_KING; ++currentChess)
	{
		GenerateMoves(static_cast<Chess>(currentChess), a_board);
	}

	return m_moves->Count();
}

uint8 MoveGenerator::GenerateBlkCaptureMoves(Board &a_board)
{
    m_moves->Clear();

    for (int currentChess = BLK_PAWN_1; currentChess <= BLK_KING; ++currentChess)
    {
        GenerateCaptureMoves(static_cast<Chess>(currentChess), a_board);
    }

    return m_moves->Count();
}

void MoveGenerator::GenerateMoves(Chess a_chess, Board &a_board)
{
	if (a_board.IsDead(a_chess) ||
		!s_generatorByChess[a_chess])
	{
		return;
	}

	s_generatorByChess[a_chess]->GenerateMoves(a_board.GetPos(a_chess), a_board, *m_moves);
}

void MoveGenerator::GenerateCaptureMoves(Chess a_chess, Board &a_board)
{
    if (a_board.IsDead(a_chess) ||
        !s_generatorByChess[a_chess])
    {
        return;
    }

    s_generatorByChess[a_chess]->GenerateCaptureMoves(a_board.GetPos(a_chess), a_board, *m_moves);
}

const MovePos *MoveGenerator::GetMove(uint8 a_index) const
{
	return m_moves->GetMove(a_index);
}