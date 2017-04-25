#ifndef BITBOARDS_H_INCLUDED
#define BITBOARDS_H_INCLUDED

#include "libraries.h"
using namespace std;

enum chess_piece{king, queen, bishop, knight, rook, pawn, blank};
enum colour{white, black};


// Coordinate system
struct coord
{
    int x;
    int y;
};

coord toCoord(int x, int y);

struct pieces
{
    coord location;
    vector <coord> attack;
    chess_piece what_piece;
    colour side;
};
// 8x8 board of pieces
struct pieceBoard
{
    pieces board[8][8];
};

// Find possible moves
void moves(pieces &piece, pieceBoard board);




// 8x8 board of integers
struct bitboard
{
    int board[8][8];
};

// Add and subtract bitboards
bitboard operator +(bitboard first, bitboard second);
bitboard operator -(bitboard first, bitboard second);

void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
