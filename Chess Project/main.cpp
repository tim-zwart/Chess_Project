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
    Piece whitePawn(toCoord(5, 5), pawn, white);
    Piece whiteRook(toCoord(5, 6), rook, white);
    Piece whiteKing(toCoord(5, 4), king, white);
    Piece blackPawn(toCoord(4, 6), pawn, black);
    Piece blackBishop(toCoord(4, 5), bishop, black);
    Piece blackQueen(toCoord(6, 5), queen, black);
    pieceBoard b;

    // Bitboard for the squares that white is attacking
    bitboard attackWhite;

    // Bitboard for the squares that black is attacking
    bitboard attackBlack;

    b.board[5][5]=whitePawn;
    b.board[5][6]=whiteRook;
    b.board[5][4]=whiteKing;
    b.board[4][6]=blackPawn;
    b.board[4][5]=blackBishop;
    b.board[6][5]=blackQueen;
    b.board[5][5].moves(b);
    b.board[5][6].moves(b);
    b.board[5][4].moves(b);
    b.board[4][6].moves(b);
    b.board[4][5].moves(b);
    b.board[6][5].moves(b);
    b.board[5][5].testing();
    b.board[5][6].testing();
    b.board[5][4].testing();
    b.board[4][6].testing();
    b.board[4][5].testing();
    b.board[6][5].testing();

    calcBoard(attackWhite, b, white);
    calcBoard(attackBlack, b, black);

    // Output all of the squares that white is attacking
    for (int i=7; i>=0; i--)
    {
        for (int j=0; j<8; j++)
            cout << attackWhite.board[j][i] << " ";
        cout << endl;
    }

    cout << endl << endl;

    // Output all of the squares that black is attacking
    for (int i=7; i>=0; i--)
    {
        for (int j=0; j<8; j++)
            cout << attackBlack.board[j][i] << " ";
        cout << endl;
    }

    return 0;
}
