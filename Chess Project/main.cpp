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

    b.calculate(white);
    b.calculate(black);
    b.do_move(convert("e5"), convert("e4"));
    b.calculate(white);
    b.calculate(black);
    b.do_move(convert("d7"), convert("d5"));
    b.calculate(black);
    b.calculate(white);
    cout<<b<<endl;

<<<<<<< HEAD
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

    b.do_move(toCoord(6, 1), toCoord(6, 3));

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

    b.evalBoard();

    // Output board
    cout << b << endl;

    cout << "Score: " << b.score << endl;

    cout<<"White Attacking "<<b.white_attack;
    cout<<"Black Attacking "<<b.black_attack;

    string loc = "d2";
    coord c = convert(loc);
    cout << "x: " << c.x << "  y: " << c.y << endl;

    return 0;
=======
>>>>>>> refs/remotes/origin/master
}
