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
    /*Board b;
    b.calcMoves(white);
    return 0;*/
    // Declare chessboard
    node *n = new node;
    n->container.reset();
    //n->container.evalBoard();
    //cout << n->container.score << endl;
    /*
        n->container.do_move(convert(convert("d2"), convert("d4")));
        n->container.do_move(convert(convert("e7"), convert("e5")));
        n->container.do_move(convert(convert("d4"), convert("e5")));
        n->container.do_move(convert(convert("b8"), convert("c6")));
    */
/*
    n->container.calcMoves(black);
    n->container.calcBoard(black);
    n->container.calcMoves(white);
    vector <buff_pair> pairs;
    for(int i=0;i<n->container.moves.size();i++)
    {
        buff_pair temp;
        temp.thisMove = n->container.moves[i];
        temp.score = breadth_search(n->container, 2, 0, n->container.moves[i], black, 0, false, false);
        pairs.push_back(temp);
    }

    sort(pairs.begin(), pairs.end(), compareByScore);

    for(int i=0; i<pairs.size(); i++)
    {
        convert(pairs[i].thisMove.start_loc);
        cout<<" to ";
        convert(pairs[i].thisMove.end_loc);
        cout<<endl;
    }
*/

    cout << "Which side should the computer play as? 0 for white, 1 for black" << endl;
    colour side;

    do
    {
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
    }
    while(true);

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
        case end_game:
            cout << "Aborting" << endl;
            return 0;
        default:
            break;
        }

        // Change who's turn it is to move
        turn = colour(!bool(turn));
    }

    return 0;
}
