#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

void generate_move(pieceBoard Board);
void calcMoves(pieceBoard &board, bitboard attackBoard, colour side);
// Saves the movement
int move_piece(pieceBoard &main_board, coord start, coord endLoc);
int move_selection(bitboard main_board);

void all_moves_gen(pieceBoard Board, colour side, cvec& checks, cvec& capture, cvec& quiet);

#endif // MOVEGEN_H_INCLUDED
