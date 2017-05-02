// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<attacked> avec;

void calcMoves(pieceBoard &board, bitboard attackBoard, colour side)
{
    vector <int> moves;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if(board.board[i][j].side==side)
                board.board[i][j].moves(board, attackBoard);
        }
    }
}

