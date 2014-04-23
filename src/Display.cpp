#include <cstdio>
#include <cstring>
#include "Display.h"
#include "Board.h"

const wchar_t Display::s_defaultBoard[BOARD_SIZE + 1] = {
	L"　　　　　　　　　　"
	L"\n┌┬┬┬┬┬┬┬┐"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n├┴┴┴┴┴┴┴┤"
	L"\n├┬┬┬┬┬┬┬┤"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n├┼┼┼┼┼┼┼┤"
	L"\n└┴┴┴┴┴┴┴┘"
	L"　　　　　　　　　\n"
};

const wchar_t Display::s_chessChar[MAX_CHESS] = {
	L'＋',				              // NONE
	L'卒', L'卒', L'卒', L'卒', L'卒',// Black Pawn
	L'包', L'包',				      // Black Cannon
	L'馬', L'馬',				      // Black Horse
	L'車', L'車',				      // Black Rook
	L'象', L'象',				      // Black Elephant
	L'士', L'士',				      // Black Guard
	L'將',					          // Black King
	L'　',				              // BOUNDARY
	L'兵', L'兵', L'兵', L'兵', L'兵',// Red Pawn
	L'炮', L'炮',				      // Red Cannon
	L'碼', L'碼',				      // Red Horse
	L'硨', L'硨',				      // Red Rook
	L'相', L'相',				      // Red Elephant
	L'仕', L'仕',				      // Red Guard
	L'帥',					          // Red King
};

Display::Display()
{
	memset(m_currentBoard, 0, sizeof(wchar_t) * (BOARD_SIZE + 1));
}

void Display::Print(const Board &a_board)
{
	wcscpy(m_currentBoard, s_defaultBoard);

	for (int currentChess = BLK_PAWN_1; currentChess <= BLK_KING; ++currentChess)
	{
		if (!a_board.IsDead(static_cast<Chess>(currentChess)))
		{
			m_currentBoard[a_board.GetPos(static_cast<Chess>(currentChess))] = s_chessChar[currentChess];
		}
	}

	for (int currentChess = RED_PAWN_1; currentChess <= RED_KING; ++currentChess)
	{
		if (!a_board.IsDead(static_cast<Chess>(currentChess)))
		{
			m_currentBoard[a_board.GetPos(static_cast<Chess>(currentChess))] = s_chessChar[currentChess];
		}
	}

	wprintf(m_currentBoard);
}