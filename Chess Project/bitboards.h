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

    // Whic colour the piece is
    colour side;

    // What type of piece it is
    chess_piece what_piece;

    // The location of the piece
    coord location;

    // Testing functions
    void testing();
    void convert(coord position);
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
    // Initialize the board
    Board();

    // Output control board
    void outputBoard(colour side);

    // Reset the board to the starting configuration
    void reset();

    // Calculate control board
    void calcBoard(colour side);

    //
    void generate_move();

    // Calculate all possible moves from a position
    void calcMoves(colour side);

    // Test a piece on the board
    void testing(int x, int y);
};

// Output board
ostream & operator<<(ostream & stream, Board b);

#endif // BITBOARDS_H_INCLUDED
