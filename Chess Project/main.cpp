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
    pieceBoard b;
    for (int i=0;i<8;i++)
        for (int j=0;j<8;j++)
            b.board[i][j].what_piece = blank;
    b.board[1][1].what_piece = pawn;
    b.board[1][1].side=white;
    b.board[1][1].location.x=1;
    b.board[1][1].location.y=1;
    b.board[2][2].what_piece = pawn;
    b.board[2][2].side=black;
    b.board[2][2].location.x=2;
    b.board[2][2].location.y=2;
    moves(b.board[2][2], b);

    for (int i=0; i<b.board[2][2].attack.size(); i++)
    {
        cout << "x: " << b.board[2][2].attack[i].x << endl;
        cout << "y: " << b.board[2][2].attack[i].y << endl;
        cout << endl;
    }

    return 0;
}
