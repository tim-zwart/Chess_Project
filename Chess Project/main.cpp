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
    Piece whiteRook(toCoord(0, 0), rook, white);
    Piece whiteRook2(toCoord(7, 0), rook, white);
    Piece whiteKing(toCoord(4, 0), king, white);
    Piece blackPawn(toCoord(4, 6), pawn, black);
    Piece blackBishop(toCoord(4, 5), bishop, black);
    Piece blackQueen(toCoord(6, 5), queen, black);
    pieceBoard b;

    // Bitboard for the squares that white is attacking
    bitboard attackWhite;

    // Bitboard for the squares that black is attacking
    bitboard attackBlack;

    b.board[5][5]=whitePawn;
    b.board[0][0]=whiteRook;
    b.board[7][0]=whiteRook2;
    b.board[4][0]=whiteKing;
    b.board[4][6]=blackPawn;
    b.board[4][5]=blackBishop;
    b.board[6][5]=blackQueen;
    b.board[4][6].moves(b, attackWhite);
    b.board[4][5].moves(b, attackWhite);
    b.board[6][5].moves(b, attackWhite);
    calcBoard(attackBlack, b, black);
    b.board[5][5].moves(b, attackBlack);
    b.board[0][0].moves(b, attackBlack);
    b.board[7][0].moves(b, attackBlack);
    b.board[4][0].moves(b, attackBlack);
    b.board[5][5].testing();
    b.board[0][0].testing();
    b.board[7][0].testing();
    b.board[4][0].testing();
    b.board[4][6].testing();
    b.board[4][5].testing();
    b.board[6][5].testing();

    calcBoard(attackWhite, b, white);

    // Output all of the squares that white is attacking
    outputBitboard(attackBlack);

    cout << endl << endl;

    // Output all of the squares that black is attacking
    outputBitboard(attackWhite);

    return 0;
}
