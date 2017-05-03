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

class Board;

class Piece
{
    friend class Board;
private:
    int dir;
    bool castle;
    bool enpassant;
public:
    Piece(coord, chess_piece, colour);
    Piece();
    // Find possible moves
    void moves(Board &board);
    // Saves the movement
    vector <coord> movement;
    // Saves what pieces it can attack
    attacked attack_option;
    colour side;
    chess_piece what_piece;
    coord location;

    //testing functions
    void testing();
    void convert(coord position);
    Board reset();
};

// 8x8 board of pieces
class Board
{
    friend ostream & operator<<(ostream & stream, Board b);
    friend class Piece;
private:
    Piece board[8][8];
    int whiteControl[8][8];
    int blackControl[8][8];

public:
    void outputBoard(colour side);
    void reset();


    void outputBitboard();
    void calcBoard(colour side);
    void generate_move();
    void calcMoves(colour side);
};

ostream & operator<<(ostream & stream, Board b);

//void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
