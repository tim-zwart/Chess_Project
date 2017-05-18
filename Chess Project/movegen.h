#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

const move_store noMove=convert(convert("a1"), convert("a1"));

struct node
{
    node* trunk;
    vector<node*> branches;
    Board container;
};

node* create();

void breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide);

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
