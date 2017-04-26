// Contains bitboard arguments and related functions

#include "bitboards.h"

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
    side = none;
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

void Piece::moves(pieceBoard board)
{
    switch(what_piece)
    {
    case king:
        break;

    case queen:
        break;

    case bishop:
        /*
        for (int i=1;; i++)
        {
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(i+location.x>7 || i+location.y>7 || board.board[location.x+i][location.y+i].side==side)
                break;
            if(board.board[location.x+i][location.y+i].side != side && board.board[location.x+i][location.y+i].side != none)
            {
                attack.push_back(toCoord(location.x+i, location.y+i));
                break;
            }
            attack.push_back(toCoord(location.x+i, location.y+i));
        }
        break;
        */

    case knight:
        for(int i=1;;)
        break;

    case rook:
        break;

    case pawn:
        // Moves for pawns

        // Moving forward
        if(board.board[location.x][location.y+dir].what_piece==blank)
        {
            movement.push_back(toCoord(location.x, location.y+dir));

            // Moving forward 2 from the seventh rank
            if(location.y==(3.5-2.5*dir) && board.board[location.x][location.y+2*dir].what_piece==blank)
                movement.push_back(toCoord(location.x, location.y+2*dir));
        }

        // Take to the right
        if(board.board[location.x+1][location.y+dir].what_piece!=blank && board.board[location.x+1][location.y+dir].side!=side)
        {
            attack_option.attack_coord.push_back(toCoord(location.x+1, location.y+dir));
            attack_option.which_piece.push_back(board.board[location.x + 1][location.y+dir].what_piece);
        }
        // Take to the left
        if(board.board[location.x-1][location.y+dir].what_piece!=blank && board.board[location.x-1][location.y+dir].side!=side)
        {
            attack_option.attack_coord.push_back(toCoord(location.x-1, location.y+dir));
            attack_option.which_piece.push_back(board.board[location.x + 1][location.y + dir].what_piece);
        }
        //
        // Insert En Passant
        //

        break;

    default:
        return;
    }

    return;
}

void Piece::convert(coord position)
{
    cout<<(char)(position.x + 97);

    cout<<position.y + 1;
}

void Piece::testing()
{
    cout<<"Attacking:";
    for(int i = 0; i < attack_option.attack_coord.size(); i++)
    {
        convert(location);
        cout<<"x";
        convert(attack_option.attack_coord[i]);
        cout<<" ";
    }
    cout<<endl;
    cout<<"Movement:";
    for(int i = 0; i < movement.size(); i++)
    {
        convert(movement[i]);
        cout<<" ";
    }
}
