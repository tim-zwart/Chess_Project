#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

struct buff_pair
{
    move_store thisMove;
    int score;
};

bool compareByScore(const buff_pair &a, const buff_pair &b);

const move_store noMove=convert(convert("a1"), convert("a1"));

gameState compMove(colour side, Board &b, vector<move_history> &history);

// Get input for move
gameState getMove(colour side, Board &b, vector<move_history> &history);

int breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, move_store* chosenMove, bool depth, bool searchDeeper);
int depth_search(Board b, int ply, int current_ply, colour side, move_store thisMove);

typedef vector<attacked> avec;
typedef vector<coord> cvec;

#endif // MOVEGEN_H_INCLUDED
