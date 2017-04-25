// Contains bitboard arguments and related functions

#include "bitboards.h"

bool king_loc[8][8];
bool king_attack[8][8];

bitboard operator +(bitboard first, bitboard second)
{
    // Add boards
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
            first.board[i][j]+=second.board[i][j];
    }
    return first;
}

bitboard operator -(bitboard first, bitboard second)
{
    // Subtract boards
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
            first.board[i][j]-=second.board[i][j];
    }
    return first;
}

coord toCoord(int x, int y)
{
    coord c;
    c.x=x;
    c.y=y;
    return c;
}

Piece::Piece()
{
    what_piece = blank;
}

Piece::Piece(coord l, chess_piece p, colour s)
{
    location=l;
    what_piece=p;
    side=s;
    if(s==white)
        dir=1;
    else
        dir=-1;
}

Piece::Piece(int x, int y, chess_piece p, colour s)
{
    coord c;
    c.x=x;
    c.y=y;
    location=c;
    what_piece=p;
    side=s;
    if(s==white)
        dir=1;
    else
        dir=-1;
}

void Piece::moves(pieceBoard board)
{
    switch(what_piece)
    {
    case king:
        break;

    case queen:
        break;

    case bishop:
        for (int i=1;; i++)
        {
            if(i+location.x>7 && 1+location.y>7)
                break;
            if(board.board[location.x+i][location.y+i].what_piece==blank)
                attack.push_back(toCoord(location.x+i, location.y+i));
            else if(board.board[location.x+i][location.y+i].side != side)
            {
                attack.push_back(toCoord(location.x+i, location.y+i));
                break;
            }
        }
        break;

    case knight:
        break;

    case rook:
        break;

    case pawn:
        // Moves for pawns

        // Moving forward
        if(board.board[location.x][location.y+dir].what_piece==blank)
        {
            attack.push_back(toCoord(location.x, location.y+dir));

            // Moving forward 2 from the seventh rank
            if(location.y==(3.5-2.5*dir) && board.board[location.x][location.y+2*dir].what_piece==blank)
                attack.push_back(toCoord(location.x, location.y+2*dir));
        }

        // Take to the right
        if(board.board[location.x+1][location.y+dir].what_piece!=blank && board.board[location.x+1][location.y+dir].side!=side && location.x<7)
            attack.push_back(toCoord(location.x+1, location.y+dir));

        // Take to the left
        if(board.board[location.x-1][location.y+dir].what_piece!=blank && board.board[location.x-1][location.y+dir].side!=side && location.x>0)
            attack.push_back(toCoord(location.x-1, location.y+dir));

        //
        // Insert En Passant
        //

        break;

    default:
        return;
    }

    return;
}
