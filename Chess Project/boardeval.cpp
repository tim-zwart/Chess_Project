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

int calc_develop()
{
	return 0;
}

int calc_saftey()
{
	return 0;
}

bool Board::calc_Bishop(int x ,int y)
{
    //board.board[x][y]

    int mobility = 0;
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
	return true;
}

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
                positionalScore += 3;
            else if(board[x][y].side == black)
                positionalScore -= 3;
			/*
            if(whiteControl[x][y] != 0)
                positionalScore += 2 * whiteControl[x][y];
            else if(blackControl[x][y] != 0)
                positionalScore -= 2 * blackControl[x][y];
			*/
        }
    }
	/*
    for(int i = 0; i < 8; i++)
    {
        if((board[0][i].what_piece != bishop || board[0][i].what_piece != knight) && board[7][i].side == white)
            positionalScore += 2;
        if ((board[7][i].what_piece != bishop || board[7][i].what_piece != knight) && board[7][i].side == black)
            positionalScore -= 2;
    }*/
/*
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if(board[x][y].what_piece == bishop)
            {
                if(calc_Bishop(x, y))
                    positionalScore += 2;
                else
                    positionalScore -= 2;
            }
            else if(board[x][y].what_piece == king)
            {
                if(calc_saftey())
                    positionalScore += 2;
                else
                    positionalScore -= 2;
            }
        }
    }*/

    // Add positional score to the overall score
    score += positionalScore * positionalWeight;

    // Increase score by a factor of 10 to accommodate possible states, such as checkmate or stalemate
    score *= 10;
}
