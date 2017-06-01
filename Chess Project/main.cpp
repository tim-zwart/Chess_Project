// Chess Final Project
// Huck Kim and Tim Zwart
//
// Single player chess
// 2017

#include <iostream>
#include "bitboards.h"
#include "movegen.h"

using namespace std;
int countSearches = 0;
int main()
{
    // Declare chessboard
    node *n = new node;
    n->container.reset();
/*
    n->container.do_move(convert(convert("d2"), convert("d4")));
    n->container.do_move(convert(convert("e7"), convert("e5")));
    n->container.do_move(convert(convert("d4"), convert("e5")));
    n->container.do_move(convert(convert("b8"), convert("c6")));
*/
    cout << "Which side should the computer play as? 0 for white, 1 for black" << endl;
    colour side;

    do
    {countSearches = 0;
        int num;
        cin >> num;

        if(cin.fail() || (num != 0 && num != 1))
        {
            cout << "Invalid input Try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
        {
            side = (colour)num;
            break;
        }
    } while(true);

    colour turn = white;
    cout << endl;
    while(true)
    {
        // Output board
        cout << n->container << endl;

        gameState currState;

        // If it is the computer's turn, make it move
        if(turn == side)
            currState = compMove(turn, n);

        // If it is the user's turn, let them move
        else
            currState = getMove(turn, n);

        switch (currState)
        {
        case whiteWins:
            cout << "Checkmate! White wins!" << endl;
            return 0;
        case blackWins:
            cout << "Checkmate! Black wins!" << endl;
            return 0;
        case draw:
            cout << "It's a draw!" << endl;
            return 0;
        default:
            break;
        }

        // Change who's turn it is to move
        turn = colour(!bool(turn));
    }

    return 0;
}
