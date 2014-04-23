#include <cstdlib>
#include "Board.h"
#include "TranspositionTable.h"

uint32 TranspositionTable::s_countHit = 0;
uint32 TranspositionTable::s_countMiss = 0;

TranspositionTable::TranspositionTable()
    :
m_currentKey(0),
m_hashKeys(0)
{
    InitHashTables();
}

TranspositionTable::~TranspositionTable()
{
    for (int32 i = 0; i < MAX_CHESS_TYPE; ++i)
    {
        delete [] m_hashKeys[i];
    }

    delete [] m_hashKeys;
    m_hashKeys = 0;
}

void TranspositionTable::InitHashTables()
{
    srand(32);

    m_hashKeys = new uint64*[MAX_CHESS_TYPE];

    for (int32 i = 0; i < MAX_CHESS_TYPE; ++i)
    {
        m_hashKeys[i] = new uint64[BOARD_SIZE];

        for (int32 j = 0; j < BOARD_SIZE; ++j)
        {
            m_hashKeys[i][j] = (static_cast<uint64>(rand()) << 32) | rand();
        }
    }

    m_hashKeyRedTurn = (static_cast<uint64>(rand()) << 32) | rand();
}

void TranspositionTable::InitByBoard(int8 a_turn, const Board &a_board)
{
    m_currentKey = 0;

    for (int i = BLK_PAWN_1; i <= BLK_KING; ++i)
    {
        if (!a_board.IsDead(static_cast<Chess>(i)))
        {
            m_currentKey ^= m_hashKeys[a_board.GetType(static_cast<Chess>(i))][a_board.GetPos(static_cast<Chess>(i))];
        }
    }

    for (int i = RED_PAWN_1; i <= RED_KING; ++i)
    {
        if (!a_board.IsDead(static_cast<Chess>(i)))
        {
            m_currentKey ^= m_hashKeys[a_board.GetType(static_cast<Chess>(i))][a_board.GetPos(static_cast<Chess>(i))];
        }
    }

    if (a_turn == RED_TURN)
    {
        m_currentKey ^= m_hashKeyRedTurn;
    }
}

uint64 TranspositionTable::ChangeKeyByMoving(ChessType a_chessMoving, Pos a_from, ChessType a_chessTaken, Pos a_to)
{
    m_currentKey ^= m_hashKeys[a_chessMoving][a_from];

    if (a_chessTaken != NONE)
    {
        m_currentKey ^= m_hashKeys[a_chessTaken][a_to];
    }

    m_currentKey ^= m_hashKeys[a_chessMoving][a_to];

    // After moving, turn is changed
    m_currentKey ^= m_hashKeyRedTurn;
    
    return m_currentKey;
}

uint64 TranspositionTable::ChangeKeyByNullMove()
{
    m_currentKey ^= m_hashKeyRedTurn;

    return m_currentKey;
}

bool TranspositionTable::IsExist(uint32 a_depth, int32 &a_outScore, MovePos &a_outMove) const
{
    TTMaps::const_iterator iter = m_hashMaps.find(m_currentKey);

    if (iter != m_hashMaps.end())
    {
        if (iter->second.depth >= a_depth)
        {
            a_outScore = iter->second.score;
            a_outMove = iter->second.bestMove;
            ++s_countHit;
            return true;
        }
    }

    ++s_countMiss;

    return false;
}

void TranspositionTable::Store(uint32 a_depth, int32 a_score, const MovePos &a_bestMove)
{
    TTMaps::iterator iter = m_hashMaps.find(m_currentKey);

    if (iter == m_hashMaps.end())
    {
        m_hashMaps.insert(std::make_pair(m_currentKey, HashEntry(a_depth, a_score, a_bestMove)));
    }
    else
    {
        assert(a_depth >= iter->second.depth);

        iter->second.depth = a_depth;
        iter->second.score = a_score;
        iter->second.bestMove = a_bestMove;
    }
}