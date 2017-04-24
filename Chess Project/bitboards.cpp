// Contains bitboard arguments and related functions

#include "bitboards.h"

bool king_loc[8][8];
bool king_attack[8][8];

operator +(bitboard first, bitboard second)
{
    // Add boards
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
            first->board[i][j]+=second->board[i][j];
    }
    return first;
}

operator -(bitboard first, bitboard second)
{
    // Subtract boards
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
            first->board[i][j]-=second->board[i][j];
    }
    return first;
}
