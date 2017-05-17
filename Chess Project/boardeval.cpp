#include "boardeval.h"
#include "bitboards.h"
#include "movegen.h"

// Weight of aspects of the board
const int materialWeight=10;
const int positionalWeight=1;

// Weight of pieces
const int kingWeight=1000;
const int queenWeight=9;
const int rookWeight=5;
const int bishopWeight=3;
const int knightWeight=3;
const int pawnWeight=1;

void Board::evalBoard()
{
    // Reset score
    score = 0;

    // Store material score
    int materialScore = kingWeight   * (wK-bK) +
                        queenWeight  * (wQ-bQ) +
                        rookWeight   * (wR-bR) +
                        bishopWeight * (wB-bB) +
                        knightWeight * (wN-bN) +
                        pawnWeight   * (wP-bP);

    // Search for pieces
    /*for (int x=0; x<8; x++)
        for (int y=0; y<8; y++)
        {
            // Calculate material advantages
            switch(board[x][y].what_piece)
            {
            case king:
                materialScore += kingWeight*board[x][y].dir;
                break;
            case queen:
                materialScore += queenWeight*board[x][y].dir;
                break;
            case rook:
                materialScore += rookWeight*board[x][y].dir;
                break;
            case bishop:
                materialScore += bishopWeight*board[x][y].dir;
                break;
            case knight:
                materialScore += knightWeight*board[x][y].dir;
                break;
            case pawn:
                materialScore += pawnWeight*board[x][y].dir;
                break;
            default:
                break;
            }
        }*/

    // Add material scores to the total score
    score+=materialScore*materialWeight;
}
