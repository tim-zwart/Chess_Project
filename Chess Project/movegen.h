#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

const move_store noMove=convert(convert("a1"), convert("a1"));

void compMove(colour side, node *&n);

// Get input for move
void getMove(colour side, node *&n);

int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first);

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
