#include "boardeval.h"
#include "bitboards.h"
#include "movegen.h"

// Weight of aspects of the board
const int materialWeight=10;
const int positionalWeight=1;

// Weight of pieces
const int pieceWeight[] =
{
1000, // King
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
}
