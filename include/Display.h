#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Common.h"

class Board;

class Display
{
public:

	Display();

	void Print(const Board &a_board);

private:

	static const wchar_t s_chessChar[MAX_CHESS];
	static const wchar_t s_defaultBoard[BOARD_SIZE + 1];

	wchar_t m_currentBoard[BOARD_SIZE + 1];
};

#endif // ifndef __DISPLAY_H__