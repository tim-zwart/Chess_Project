#ifndef BITBOARDS_H_INCLUDED
#define BITBOARDS_H_INCLUDED

#include "libraries.h"

enum chess_piece {king, queen, bishop, knight, rook, pawn, blank};
enum colour {white, black, none};


// Coordinate system
struct coord
{
    int x;
    int y;
};

struct attacked
{
    vector <coord> attack_coord;
    vector <chess_piece> which_piece;
};

coord toCoord(int x, int y);
struct pieceBoard;
class Piece
{
private:
    coord location;
    chess_piece what_piece;
    colour side;
    int dir;
public:
    Piece(coord, chess_piece, colour);
    Piece();
    // Find possible moves
    void moves(pieceBoard board);
    // Saves the movement
    vector <coord> movement;
    // Saves what pieces it can attack
    attacked attack_option;

    //testing functions
    void testing();
    void convert(coord position);
};

// 8x8 board of pieces
struct pieceBoard
{
    Piece board[8][8];
};

// 8x8 board of integers
struct bitboard
{
    int board[8][8];
};

// Add and subtract bitboards
bitboard operator +(bitboard first, bitboard second);
bitboard operator -(bitboard first, bitboard second);

//void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
