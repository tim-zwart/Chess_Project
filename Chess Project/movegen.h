#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

struct eval_pair
{
    move_store curr_move;
    int score;
};

const move_store noMove=convert(convert("a1"), convert("a1"));

gameState compMove(colour side, node *&n);

// Get input for move
gameState getMove(colour side, node *&n);

int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first);

<<<<<<< HEAD
int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first);
void depth_search(node *parent, int ply, int current_ply, colour side, int white_score, int black_score, bool first, vector <move_store> &moves);
=======
void breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, node *parent);
void depth_search(Board& input_board, int ply, int current_ply, colour side, Board& start_board);

int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide);

>>>>>>> refs/remotes/origin/master

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
