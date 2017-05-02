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

// 8x8 board of integers
struct bitboard
{
    int board[8][8];
};

void outputBitboard(bitboard board);

coord toCoord(int x, int y);

struct pieceBoard;

class Piece
{
private:
    int dir;
    bool castle;
    bool enpassant;
public:

    //constructor
    Piece(coord, chess_piece, colour);
    Piece();

    /**< Moving Functions */
    // Find possible moves
    void moves(pieceBoard board, bitboard attackBoard);
    // Saves the movement
    int move_piece(color side, pieceBoard &main_board, coord start, coord endLoc);

    /**< Saved Values */
    vector <coord> movement;
    // Saves what pieces it can attack
    attacked attack_option;
    // Saves pieces side black, white, or none
    colour side;
    // Saves what piece it is
    chess_piece what_piece;
    // Saves it's lcoation
    coord location;

    /**< Testing Functions */
    void testing();
    void convert(coord position);
    pieceBoard reset();
    void piece_clear();
};

// 8x8 board of pieces
struct pieceBoard
{
    Piece board[8][8];
    Piece *movedDouble;
};

void resetBoard (pieceBoard &b);
void calcBoard(bitboard &write, pieceBoard b, colour side);

// Add and subtract bitboards
bitboard operator +(bitboard first, bitboard second);
bitboard operator -(bitboard first, bitboard second);

//void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
