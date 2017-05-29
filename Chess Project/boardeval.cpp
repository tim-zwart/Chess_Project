#include "boardeval.h"
#include "bitboards.h"
#include "movegen.h"

// Weight of aspects of the board
const int materialWeight=10;
const int positionalWeight=1;

// Weight of pieces
const int pieceWeight[] =
{
5000, // King
9,    // Queen
5,    // Rook
3,    // Bishop
3,    // Knight
1     // Pawn
};

void Board::evalBoard()
{
    // Reset score
    score = 0;

    // Store material score
    int materialScore = 0;
    for(int i=0;i<6;i++)
        materialScore += pieceWeight[i] * (w[i] - b[i]);

    // Add material scores to the total score
    score += materialScore*materialWeight;

    //outputBoard(white);

    for(int x = 3; x < 5; x++)
    {
        for(int y = 3; y < 5; y++)
        {
            if(board[x][y].side == white)
                score += 3;
            else if(board[x][y].side == black)
                score -= 3;
            if(whiteControl[x][y] != 0)
                score += 2 * whiteControl[x][y];
            else if(blackControl[x][y] != 0)
                score -= 2 * blackControl[x][y];
        }
    }

    for(int i = 0; i < 8; i++)
    {
        if((board[0][i].what_piece != bishop || board[0][i].what_piece != knight) && board[7][i].side == white)
            score += 1;
        if ((board[7][i].what_piece != bishop || board[7][i].what_piece != knight) && board[7][i].side == black)
            score -= 1;
    }
    // Increase score by a factor of 10 to accommodate possible states, such as checkmate or stalemate
    score *= 10;
}
