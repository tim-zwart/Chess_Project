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
    node *head = create(b);
    breadth_search(b, 4, 0, noMove, white, head);
    /*
    b.do_move(convert(convert("e2"), convert("e4")));
    b.calculate(white);
    b.calculate(black);
    b.do_move(convert(convert("d7"), convert("d5")));
    b.calculate(black);
    b.calculate(white);
    b.do_move(convert(convert("e4"), convert("d5")));
    cout<<b<<endl;
    b.evalBoard();
    cout << "Score:" << b.score << endl << endl;
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

    //b.do_move(toCoord(6, 1), toCoord(6, 3));

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

    cout<<"White Attacking "<<b.white_attack;
    cout<<"Black Attacking "<<b.black_attack;*/

    return 0;
}
