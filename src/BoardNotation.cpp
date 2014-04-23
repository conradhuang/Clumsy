#include <sstream>
#include "BoardNotation.h"
#include "Board.h"
#include "Common.h"
#include "Types.h"

namespace Notation
{
const char g_charChessType[MAX_CHESS_TYPE] = {
    ' ', // EMPTY
    'p', // BP
    'c', // BC
    'n', // BH
    'r', // BR
    'b', // BE
    'a', // BG
    'k', // BK
    ' ', // BNDRY
    'P', // RP
    'C', // RC
    'N', // RH
    'R', // RR
    'B', // RE
    'A', // RG
    'K'  // RK
};

std::string ToFEN(const Board &a_board)
{
    uint32 countEmptyPos = 0;
    std::stringstream outStr;

    for (int32 i = L11; i < L110; ++i)
    {
        if (a_board.IsEmpty(i))
        {
            ++countEmptyPos;
        }
        else
        {
            if (countEmptyPos > 0)
            {
                outStr << countEmptyPos;
                countEmptyPos = 0;
            }

            if (a_board.IsBoundary(i))
            {
                outStr << '/';
            }
            else
            {
                outStr << g_charChessType[a_board.GetType(a_board[i])];
            }
        }
    }

    return outStr.str();
}

bool IsNumber(const char a_char)
{
    return a_char >= '1' && a_char <= '9';
}

int32 ToInt(const char a_char)
{
    assert(IsNumber(a_char));

    return a_char - '0';
}

void InitBoardByFEN(const std::string &a_FEN, Board &a_outBoard)
{
    std::string::const_iterator iter = a_FEN.begin();
    Pos pos = L11;
    char charChess[MAX_CHESS] = {
        ' ',
        'p', 'p', 'p', 'p', 'p',
        'c', 'c',
        'n', 'n',
        'r', 'r',
        'b', 'b',
        'a', 'a',
        'k',
        ' ',
        'P', 'P', 'P', 'P', 'P',
        'C', 'C',
        'N', 'N',
        'R', 'R',
        'B', 'B',
        'A', 'A',
        'K'
    };

    a_outBoard.Purge();

    for (; iter != a_FEN.end(); ++iter)
    {
        if (IsNumber(*iter))
        {
            pos += ToInt(*iter);
            continue;
        }

        if ('/' == *iter)
        {
            ++pos;
            continue;
        }

        for (int i = BLK_PAWN_1; i <= RED_KING; ++i)
        {
            if (charChess[i] == *iter)
            {
                a_outBoard.SetPos(static_cast<Chess>(i), pos);
                ++pos;
                charChess[i] = ' ';

                break;
            }
        }
    }

    for (int i = BLK_PAWN_1; i <= RED_KING; ++i)
    {
        if (charChess[i] != ' ')
        {
            a_outBoard.SetDead(static_cast<Chess>(i));
        }
    }
}

}