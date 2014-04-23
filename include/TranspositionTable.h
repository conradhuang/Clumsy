#ifndef __TRANSPOSITION_TABLE_H__
#define __TRANSPOSITION_TABLE_H__

#include <hash_map>
#include "Common.h"
#include "Types.h"

class Board;

class TranspositionTable
{
public:

    TranspositionTable();
    ~TranspositionTable();

    void InitByBoard(int8 a_turn, const Board &a_board);

    uint64 GetCurrentKey() const
    {
        return m_currentKey;
    }

    uint64 ChangeKeyByMoving(ChessType a_chessMoving, Pos a_from, ChessType a_chessTaken, Pos a_to);
    uint64 ChangeKeyByNullMove();
    bool IsExist(uint32 a_depth, int32 &a_outScore, MovePos &a_outMove) const;
    void Store(uint32 a_depth, int32 a_score, const MovePos &a_bestMove);

    static uint32 s_countHit;
    static uint32 s_countMiss;

private:

    void InitHashTables();

    struct HashEntry
    {
        HashEntry()
            :
        depth(0),
        score(0)
        {
        }

        HashEntry(uint32 a_depth, int32 a_score, const MovePos &a_bestMove)
        {
            depth = a_depth;
            score = a_score;
            bestMove = a_bestMove;
        }

        uint32 depth;
        int32 score;
        MovePos bestMove;
    };

    typedef stdext::hash_map<uint64, HashEntry> TTMaps;
    TTMaps m_hashMaps;

    uint64 **m_hashKeys;
    uint64 m_hashKeyRedTurn;
    uint64 m_currentKey;
};

#endif // #ifndef __TRANSPOSITION_TABLE_H__