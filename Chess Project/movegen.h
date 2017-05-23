#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

const move_store noMove=convert(convert("a1"), convert("a1"));

struct node
{
    node* trunk;
    vector<node*> branches;
    Board *container;
};

node* create(Board b);

void breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, node *parent);
void depth_search(Board& input_board, int ply, int current_ply, colour side, Board& start_board);

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
