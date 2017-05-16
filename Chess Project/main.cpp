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
    b.do_move(convert("e2"), convert("e4"));
    b.calculate(white);
    b.calculate(black);
    b.do_move(convert("d7"), convert("d5"));
    b.calculate(black);
    b.calculate(white);

    b.generate_move(white);
    cout<<b.white_attack<<endl;
    cout<<b<<endl;

}
