// Chess Final Project
// Huck Kim and Tim Zwart
//
// Single player chess
// 2017

#include <iostream>
#include "bitboards.h"

using namespace std;

int main()
{
<<<<<<< HEAD

=======
    pieceBoard b;

    // Bitboard for the squares that white is attacking
    bitboard attackWhite;

    // Bitboard for the squares that black is attacking
    bitboard attackBlack;

    // Set the board to the default starting position
    resetBoard(b);

    // Calculate the squares that white is attacking
    calcBoard(attackWhite, b, white);

    // Output all of the squares that white is attacking
    outputBitboard(attackBlack);

    cout << endl << endl;

    // Output all of the squares that black is attacking
    outputBitboard(attackWhite);

    return 0;
>>>>>>> refs/remotes/origin/master
}
