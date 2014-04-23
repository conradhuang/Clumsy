#include <locale.h>
#include <cstdio>
#include <ctime>
#include "Board.h"
#include "Display.h"
#include "Evaluator.h"
#include "AlphaBetaAlgorithm.h"
#include "MinMaxAlgorithm.h"
#include "NegamaxAlgorithm.h"
#include "MoveGenerator.h"
#include "TranspositionTable.h"
#include "BoardNotation.h"

int main()
{
	setlocale(LC_ALL, "");

	Board::Init();
	MoveGenerator::Init();

	Board board;
    AlphaBetaAlgorithm algorithm;
    Evaluator evaluator;

    char ch = 0;
    int32 turn = RED_TURN;
    Display display;
    uint32 countPlay = 1;

    //Notation::InitBoardByFEN("3ak1b1r/4a4/4b1n2/p3p3p/c7c/8C/P3P1P1P/2N1BR3/9/2BAKA1N", board);

    while ((ch = getchar()) != 'q')
    {
        clock_t clockBegin = clock();
        uint32 countNodes = 0;
        
        extern uint32 g_countNullMovePrunned;
        g_countNullMovePrunned = 0;
        TranspositionTable::s_countHit = 0;
        TranspositionTable::s_countMiss = 0;

        int32 score = 0;
        
        algorithm.BeginSearch(turn, 6, board, evaluator, countNodes);
        
        const BestMoves &bestMoves = algorithm.GetBestMoves();
        BestMoves::const_iterator iter = bestMoves.begin();
        
        if (iter != bestMoves.end())
        {
            board.Move(0, (*iter).from, (*iter).to);
            printf("Play = %d\n", countPlay++);
            display.Print(board);
            const float timeElapsed = static_cast<float>(clock() - clockBegin) / CLOCKS_PER_SEC;

            printf("Move From %d to %d\n", (*iter).from, (*iter).to);

            printf("Nodes = %u, Score = %d, Time = %.2fs, NPS = %.2f, Null-Move Prunned : %d\n", 
                countNodes, 
                evaluator.Evaluate(board), 
                timeElapsed,
                countNodes / timeElapsed,
                g_countNullMovePrunned);

            float totalCount = TranspositionTable::s_countHit + TranspositionTable::s_countMiss;

            printf("Hit = %d (%.2f %%), Miss = %d (%.2f %%)\n", 
                TranspositionTable::s_countHit, 
                TranspositionTable::s_countHit / totalCount * 100.0f,
                TranspositionTable::s_countMiss,
                TranspositionTable::s_countMiss / totalCount * 100.0f
                );

            printf("%s\n", Notation::ToFEN(board).c_str());
        }

        turn = -turn;
    }

    MoveGenerator::Release();

	return 0;
}