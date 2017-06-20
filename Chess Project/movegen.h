#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

// Links the move_store witb it's score value, move store is the start and end coord location
struct buff_pair
{
    move_store thisMove;
    int score;
};

// Used to represent no move for first time run of the searches
const move_store noMove=convert(convert("a1"), convert("a1"));

gameState compMove(colour side, Board &b, vector<move_history> &history);

// Get input for move
gameState getMove(colour side, Board &b, vector<move_history> &history);

/// Prototype for the two searches
// Breadth first search
int breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, move_store* chosenMove, bool depth, bool searchDeeper);
// Depth first search
int depth_search(Board b, int ply, int current_ply, colour side, move_store thisMove);

// Typedefs for vector of coords to shorten
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
