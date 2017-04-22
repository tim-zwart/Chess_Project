#ifndef BITBOARDS_H_INCLUDED
#define BITBOARDS_H_INCLUDED

enum chess_piece{king, queen, bishop, knight, rook, pawn};

struct pieces
{
    bool location[8][8];
    bool position[8][8];
    chess_piece what_piece;
};

void reset(pieces * piece);

#endif // BITBOARDS_H_INCLUDED
