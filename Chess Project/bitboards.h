#ifndef BITBOARDS_H_INCLUDED
#define BITBOARDS_H_INCLUDED

#include "libraries.h"

enum chess_piece {king = 0, queen = 1, rook = 2, bishop = 3, knight = 4, pawn = 5, blank};
enum colour {white = 0, black = 1, none};
enum moveStates {stalemate = 1, checkmate = 2, illegal = 3, takeKing = 4};
enum gameState {whiteWins = 0, blackWins = 1, draw = 2, continuing = 3, end_game = 4};

struct node;

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
    int eval;
};

struct move_history
{
    move_store thisMove;
    bool capture;
    bool check;
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
    void moves(Board &board, bool movePiece);

    // Whic colour the piece is
    colour side;

    // What type of piece it is
    chess_piece what_piece;

    // The location of the piece
    coord location;

    // Clears a piece
    void piece_clear();

    // Assignment operator for pieces
    void operator =(const Piece& startLoc);
};

// 8x8 board of pieces
class Board
{
    // Friends of Board
    friend ostream & operator<<(ostream & stream, Board &b);
    friend class Piece;
    friend int breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, move_store* chosenMove, bool depth, bool searchDeeper);
    friend int depth_search(Board b, int ply, int current_ply, colour side, move_store thisMove);
    friend gameState getMove(colour side, Board &b, vector<move_history> &history);
    friend gameState compMove(colour side, Board &b, vector<move_history> &history);
private:

    // Coordinate for pawn that can enpassant
    coord enpassant;

    // Board of pieces
    Piece board[8][8];

    // Count of pieces
    int w[6];
    int b[6];

    // Check
    bool check[2];

    // If the king or rook has moved set to false, if not true
    bool kingCastle[2];
    bool rookCastle[2];
    bool rookCastle2[2];
    bool castledKing[2];

public:

    // Stores the current score of the board
    int score;

    // Board constructor
    Board();
    // Output control board
    void outputBoard(colour side);

    // Reset the board to the starting configuration
    void reset();

    // Store all moves
    vector<move_store> moves;

    // Store what the AI considers to be the best move
    int bestMove;

    // Calculate all possible moves from a position as well as
    void calculate(colour side);

    // Applies given move to board
    void do_move(move_store thisMove, bool calc);

    // Evaluate board
    void evalBoard();

    // Assignment operator for the board
    void operator =(const Board& startLoc);
};

struct node
{
    node* trunk;
    vector<node*> branches;
    Board container;
};

// Destroy a section of a tree, starting with a node and deleting everything after it
void destroy(node *& n);

/// Several convert functions
// Output a coordinate to algebraic
void convert(coord position);
// Converts a string to a coordinate
coord convert(string s);
// Converts two coordinates to a move_store
move_store convert(coord start, coord finish);

// Output board
ostream & operator<<(ostream & stream, Board &b);
ostream & operator<<(ostream & stream, vector<coord>);

// Assignment operators
bool operator==(coord first, coord second);
bool operator==(move_store first, move_store second);
#endif // BITBOARDS_H_INCLUDED
