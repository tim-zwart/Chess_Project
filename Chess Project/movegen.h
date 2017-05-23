#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

const move_store noMove=convert(convert("a1"), convert("a1"));

void compMove(colour side, node *&n);

// Get input for move
void getMove(colour side, node *&n);

<<<<<<< HEAD
void breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, node *parent);
void depth_search(Board& input_board, int ply, int current_ply, colour side, Board& start_board);
=======
int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide);
>>>>>>> origin/master

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
