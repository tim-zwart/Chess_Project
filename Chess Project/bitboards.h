#ifndef BITBOARDS_H_INCLUDED
#define BITBOARDS_H_INCLUDED

enum chess_piece{king, queen, bishop, knight, rook, pawn};

// Add and subtract bitboards
operator +(bitboard first, bitboard second);
operator -(bitboard first, bitboard second);

// Coordinate system
struct coord
{
    int x;
    int y;
};

// 8x8 board of integers
struct bitboard
{
    int board[8][8];
};

// 8x8 board of pieces
struct pieceBoard
{
    pieces board[8][8];
};

struct pieces
{
    coord location;
    vector <coord> attack;
    bool location[8][8];
    bool attack[8][8];
    chess_piece what_piece;
};

void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
