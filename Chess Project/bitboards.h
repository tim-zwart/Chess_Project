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

    //constructor
    Piece(coord, chess_piece, colour);
    Piece();

    /**< Moving Functions */
    // Find possible moves
<<<<<<< HEAD
    void moves(pieceBoard board, bitboard attackBoard);

    /**< Saved Values */
=======
    void moves(Board &board);
    // Saves the movement
>>>>>>> refs/remotes/origin/master
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
<<<<<<< HEAD
    pieceBoard reset();
    void piece_clear();
=======
    Board reset();
>>>>>>> refs/remotes/origin/master
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
