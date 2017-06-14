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
    int positionalScore = 0;

    for(int x = 3; x < 5; x++)
    {
        for(int y = 3; y < 5; y++)
        {
            if(board[x][y].side == white)
                positionalScore += 5;
            else if(board[x][y].side == black)
                positionalScore -= 5;
        }
    }
        //board.board[x][y]

    int mobility = 0;
    /*
    int currentY1 = y;
    int currentY2 = y;

    for(int start = x; start > 0; start--)
    {
        currentY1 ++;
        currentY1 --;
        if(currentY1 >= 8 && currentY2 >= 8)
            break;
        if(board[start][currentY1].what_piece == blank)
            mobility++;
        else
            currentY1 = 8;
        if(board[start][currentY2].what_piece == blank)
            mobility++;
        else
            currentY1 = 0;
    }
    for(int start = x; start < 8; start++)
    {
        currentY1 ++;
        currentY1 --;
        if(currentY1 >= 8 && currentY2 < 0)
            break;
        if(board[start][currentY1].what_piece == blank)
            mobility++;
        else
            currentY1 = 8;
        if(board[start][currentY2].what_piece == blank)
            mobility++;
        else
            currentY1 = 0;
    }
*/
    int safety = 0;

    if(castledKing[white])
        safety += 5;
    else if(castledKing[black])
        safety -= 5;

    if(w[queen] >= 1)
    {
        if(castledKing[black] == false)
            positionalScore += 4;
    }
    if(b[queen] >= 1)
    {
        if(castledKing[white] == false)
            positionalScore += 4;
    }

    for(int i = 1; i < 7; i++)
    {
        if((board[0][i].what_piece != bishop || board[0][i].what_piece != knight) && board[7][i].side == white)
            positionalScore += 2;
        if((board[7][i].what_piece != bishop || board[7][i].what_piece != knight) && board[7][i].side == black)
            positionalScore -= 2;
    }

    // Add positional score to the overall score
    score += positionalScore * positionalWeight;
    score += mobility;

    // Increase score by a factor of 10 to accommodate possible states, such as checkmate or stalemate
    score *= 10;
}
