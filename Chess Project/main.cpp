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
    // Declare chessboard
    Board b;

    // Calculate moves for white and group onto a board
    b.calcMoves(white);
    b.calcBoard(white);

    // Calculate moves for black and group onto a board
    b.calcMoves(black);
    b.calcBoard(black);

    // Output all of the squares that white is attacking
    b.outputBoard(black);

    // Output all of the squares that black is attacking
    b.outputBoard(white);

    b.generate_move(white);
    b.generate_move(black);

    // Output board
    cout << b << endl;

    cout<<"White Attacking "<<b.white_attack;
    cout<<"Black Attacking "<<b.black_attack;

    return 0;
}
