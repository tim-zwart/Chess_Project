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
    Board b;

    // Set the board to the default starting position
    b.reset();

    b.calcMoves(white);
    b.calcBoard(white);

    b.calcMoves(black);
    b.calcBoard(black);

    // Output all of the squares that white is attacking
    b.outputBoard(black);

    cout << endl << endl;

    // Output all of the squares that black is attacking
    b.outputBoard(white);

    cout << endl << endl;

    // Output board
    cout << b << endl;

    return 0;
}
