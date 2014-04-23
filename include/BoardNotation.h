#ifndef __BOARD_NOTATION_H__
#define __BOARD_NOTATION_H__

#include <string>

class Board;

namespace Notation
{
    std::string ToFEN(const Board &a_board);
    void InitBoardByFEN(const std::string &a_FEN, Board &a_outBoard);
}

#endif // #ifndef __BOARD_NOTATION_H__