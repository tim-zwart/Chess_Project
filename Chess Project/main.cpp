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
    node *n = new node;

    cout << "Which side should the computer play as? 0 for white, 1 for black" << endl;
    colour side;
    do
    {
        int n;
        cin >> n;

        if(cin.fail() || (n != 0 && n != 1))
        {
            cout << "Invalid input Try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
        {
            side = (colour)n;
            break;
        }
    } while(true);

    colour turn = white;
    while(true)
    {
        // Output board
        cout << n->container << endl;

        // If it is the computer's turn, make it move
        if(turn == side)
            compMove(turn, n);

        // If it is the user's turn, let them move
        else
            getMove(turn, n);

        // Change who's turn it is to move
        turn = colour(!bool(turn));
    }

    return 0;
}
