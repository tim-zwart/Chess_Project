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

    return 0;
}
