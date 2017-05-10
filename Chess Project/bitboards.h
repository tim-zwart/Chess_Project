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

// Pieces that are attacked, used in Piece class
struct attacked
{
    vector <coord> attack_coord;
    vector <chess_piece> which_piece;
};

// Convert an x and a y value to a coordinate
coord toCoord(int x, int y);

class Board;

class Piece
{
    // Friends
    friend class Board;
private:
    // Direction that the piece would move in if it was a pawn
    int dir;

    // Can the piece castle (kings and rooks can't after moving)
    bool castle;

    // Can en passant be used on the piece
    bool enpassant;
public:
    // Constructors
    Piece(coord, chess_piece, colour);
    Piece();

    // Find possible moves
    void moves(Board &board);

    // Saves the movement
    vector <coord> movement;

    // Saves the squares that the piece can control
    vector <coord> control;

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
    void piece_clear();

};

// 8x8 board of pieces
class Board
{
    // Friends
    friend ostream & operator<<(ostream & stream, Board b);
    friend class Piece;

private:
    // Board of pieces
    Piece board[8][8];

    // Squares that are controlled
    int whiteControl[8][8];
    int blackControl[8][8];

public:

    //List of Coord that are being attacked
    vector <coord> white_attack;
    vector <coord> black_attack;

    // Output control board
    void outputBoard(colour side);

    void do_move(coord start_loc, coord end_loc);
    void outputBitboard();

    // Calculate control board
    void calcBoard(colour side);

    //
    void generate_move(colour side);

    // Calculate all possible moves from a position
    void calcMoves(colour side);
    void reset();
};

void convert(coord position);

// Output board
ostream & operator<<(ostream & stream, Board b);

#endif // BITBOARDS_H_INCLUDED
