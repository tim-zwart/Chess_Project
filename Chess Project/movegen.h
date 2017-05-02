#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

void generate_move(pieceBoard Board);
void calcMoves(pieceBoard &board, bitboard attackBoard, colour side);

#endif // MOVEGEN_H_INCLUDED
