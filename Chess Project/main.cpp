// Chess Final Project
// Huck Kim and Tim Zwart
//
// Single player chess
// 2017

#include <iostream>
#include "bitboards.h"
#include "movegen.h"

using namespace std;

int main()
{
    pieceBoard b;

    // Bitboard for the squares that white is attacking
    bitboard attackWhite;

    // Bitboard for the squares that black is attacking
    bitboard attackBlack;

    // Set the board to the default starting position
    resetBoard(b);

    calcMoves(b, attackBlack, white);
    calcBoard(attackWhite, b, white);

    calcBoard(attackBlack, b, black);

    // Output all of the squares that white is attacking
    outputBitboard(attackBlack);

    cout << endl << endl;

    // Output all of the squares that black is attacking
    outputBitboard(attackWhite);

    cout << endl << endl;
    b.board[0][1].testing();

    return 0;
}
