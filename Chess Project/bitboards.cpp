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
    // The 4 directions diagonal for pieces
    bool tr=true;
    bool tl=true;
    bool br=true;
    bool bl=true;

    switch(what_piece)
    {
    case king:
        break;

    case queen:
        break;

    case bishop:

        for (int i=1; i<8; i++)
        {
            // Top Right
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tr && (location.x+i>7 || location.y+i>7 || board.board[location.x+i][location.y+i].side==side))
                tr=false;
            else if(tr && board.board[location.x+i][location.y+i].side != side && board.board[location.x+i][location.y+i].side != none)
            {
                attack.push_back(toCoord(location.x+i, location.y+i));
                tr=false;
            }
            else if(tr)
                attack.push_back(toCoord(location.x+i, location.y+i));

            // Top Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tl && (location.x-i < 0 || location.y+i > 7 || board.board[location.x-i][location.y+i].side == side))
                tl=false;
            else if(tl && board.board[location.x-i][location.y+i].side != side && board.board[location.x-i][location.y+i].side != none)
            {
                attack.push_back(toCoord(location.x-i, location.y+i));
                tl=false;
            }
            else if(tl)
                attack.push_back(toCoord(location.x-i, location.y+i));

            // Bottom Right
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                br=false;
            else if(br && board.board[location.x+i][location.y-i].side != side && board.board[location.x+i][location.y-i].side != none)
            {
                attack.push_back(toCoord(location.x+i, location.y-i));
                br=false;
            }
            else if(br)
                attack.push_back(toCoord(location.x+i, location.y-i));

            // Bottom Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(bl && (location.x-i<0 || location.y-i<0 || board.board[location.x-i][location.y-i].side==side))
                bl=false;
            else if(bl && board.board[location.x-i][location.y-i].side != side && board.board[location.x-i][location.y-i].side != none)
            {
                attack.push_back(toCoord(location.x-i, location.y-i));
                bl=false;
            }
            else if(bl)
                attack.push_back(toCoord(location.x-i, location.y-i));
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
