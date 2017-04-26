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
    // The 4 diagonal directions for pieces
    bool tr=true; // Top right
    bool tl=true; // Top left
    bool br=true; // Bottom right
    bool bl=true; // Bottom left

    // The 4 non diagonal directions for pieces
    bool u=true; // Up
    bool d=true; // Down
    bool r=true; // Right
    bool l=true; // Left

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
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                tr=false;
            }
            else if(tr)
                movement.push_back(toCoord(location.x+i, location.y+i));

            // Top Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tl && (location.x-i < 0 || location.y+i > 7 || board.board[location.x-i][location.y+i].side == side))
                tl=false;
            else if(tl && board.board[location.x-i][location.y+i].side != side && board.board[location.x-i][location.y+i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y+i].what_piece);
                tl=false;
            }
            else if(tl)
                movement.push_back(toCoord(location.x-i, location.y+i));

            // Bottom Right
            // If the position is off ofconvert(movement[i]); the board or a piece of the same colour is in the way, you can't move there
            if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                br=false;
            else if(br && board.board[location.x+i][location.y-i].side != side && board.board[location.x+i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y-i].what_piece);
                br=false;
            }
            else if(br)
                movement.push_back(toCoord(location.x+i, location.y-i));

            // Bottom Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(bl && (location.x-i<0 || location.y-i<0 || board.board[location.x-i][location.y-i].side==side))
                bl=false;
            else if(bl && board.board[location.x-i][location.y-i].side != side && board.board[location.x-i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y-i].what_piece);
                bl=false;
            }
            else if(bl)
<<<<<<< HEAD
                movement.push_back(toCoord(location.x-i, location.y-i));
=======
                attack.push_back(toCoord(location.x-i, location.y-i));

            if(tr && tl && br && bl)
                break;
>>>>>>> refs/remotes/origin/master
        }
        break;

    case knight:
        for(int i = 1; ; )
        {

        }
        break;

    case rook:
        for(int i=1; i<8; i++)
        {
            // Move Up
            if(u && (location.y+i>7 || board.board[location.x][location.y+i].side == side))
                u=false;
            else if(u && board.board[location.x][location.y+i].what_piece != blank && board.board[location.x][location.y+i].side != side)
            {
                attack.push_back(toCoord(location.x, location.y+i));
                u=false;
            }
            else if (u)
                attack.push_back(toCoord(location.x, location.y+i));

            // Move Down
            if(d && (location.y-i<0 || board.board[location.x][location.y-i].side == side))
                d=false;
            else if(d && board.board[location.x][location.y-i].what_piece != blank && board.board[location.x][location.y-i].side != side)
            {
                attack.push_back(toCoord(location.x, location.y-i));
                d=false;
            }
            else if (d)
                attack.push_back(toCoord(location.x, location.y-i));

            // Move Right
            if(r && (location.x+i>7 || board.board[location.x+i][location.y].side == side))
                r=false;
            else if(r && board.board[location.x+i][location.y].what_piece != blank && board.board[location.x+i][location.y].side != side)
            {
                attack.push_back(toCoord(location.x+i, location.y));
                r=false;
            }
            else if (r)
                attack.push_back(toCoord(location.x+i, location.y));

            // Move Left
            if(l && (location.x-i<0 || board.board[location.x-i][location.y+i].side == side))
                l=false;
            else if(l && board.board[location.x-i][location.y].what_piece != blank && board.board[location.x-i][location.y].side != side)
            {
                attack.push_back(toCoord(location.x-i, location.y));
                l=false;
            }
            else if (l)
                attack.push_back(toCoord(location.x-i, location.y));
        }
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
    cout<<endl;
}
