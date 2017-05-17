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

struct move_store
{
    coord start_loc;
    coord end_loc;
};

// Pieces that are attacked, used in Piece class
struct attacked
{
    vector <coord> attack_coord;
    vector <chess_piece> which_piece;
};

struct coordPair
{
    coord startLoc;
    coord endLoc;
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
    void piece_clear();
};

// 8x8 board of pieces
class Board
{
    // Friends
    friend ostream & operator<<(ostream & stream, Board b);
    friend class Piece;
    friend void breadth_search(Board b, int maxPly, int currPly, coord start_loc, coord end_loc);

private:
    // Board of pieces
    Piece board[8][8];

    // Squares that are controlled
    int whiteControl[8][8];
    int blackControl[8][8];

    // Count of pieces
    int wK;
    int wQ;
    int wR;
    int wB;
    int wN;
    int wP;
    int bK;
    int bQ;
    int bR;
    int bB;
    int bN;
    int bP;

public:
    //List of Coord that are being attacked
<<<<<<< HEAD
    vector <coordPair> white_attack;
    vector <coordPair> black_attack;
=======
    vector <coord> white_attack;
    vector <coord> black_attack;

>>>>>>> refs/remotes/origin/master
    // Initialize the board
    Board();

    // Output control board
    void outputBoard(colour side);

    // Reset the board to the starting configuration
    void reset();

    // Calculate control board
    void calcBoard(colour side);

    //
    void generate_move(colour side);

    // Store all moves
    vector<move_store> moves;

    // Calculate all possible moves from a position
    void calcMoves(colour side);

    void do_move(move_store thisMove);

    // Evaluate board
    void evalBoard();
    int score;

    // Test a piece on the board
    void testing(int x, int y);

    void breadth_search(colour start_side, int ply, int current_ply, vector <vector<coord> >& listMoves, Board current_state);

    void depth_search(int ply, int current_ply, colour side);

    void calculate(colour side);

    void operator =(const Board& startLoc);
};

void convert(coord position);
coord convert(string s);
move_store convert(coord start, coord finish);

// Output board
ostream & operator<<(ostream & stream, Board b);
ostream & operator<<(ostream & stream, vector<coord>);
<<<<<<< HEAD
ostream & operator<<(ostream & stream, vector<coordPair> cvec);
=======
bool operator==(coord first, coord second);
>>>>>>> refs/remotes/origin/master

#endif // BITBOARDS_H_INCLUDED
