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
}

Piece::Piece(int x, int y, chess_piece p, colour s)
{
    coord c;
    c.x=x;
    c.y=y;
    location=c;
    what_piece=p;
    side=s;
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
        break;
    case knight:
        break;
    case rook:
        break;
    case pawn:
        // Moves for pawns

        // If the pawn is black
        if(side==black)
        {
            // Moving forward
            if(board.board[location.x][location.y-1].what_piece==blank)
            {
                attack.push_back(toCoord(location.x, location.y-1));

                // Moving forward 2 from the seventh rank
                if(location.y==6 && board.board[location.x][location.y-2].what_piece==blank)
                    attack.push_back(toCoord(location.x, location.y-2));
            }

            // Take to the right
            if(board.board[location.x+1][location.y-1].what_piece!=blank && board.board[location.x+1][location.y-1].side==white && location.x<7)
                attack.push_back(toCoord(location.x+1, location.y-1));

            // Take to the left
            if(board.board[location.x-1][location.y-1].what_piece!=blank && board.board[location.x-1][location.y-1].side==white && location.x>0)
                attack.push_back(toCoord(location.x-1, location.y-1));

            //
            // Insert En Passant
            //
        }

        // If the pawn is white
        if(side==white)
        {
            // Move forward
            if(board.board[location.x][location.y+1].what_piece==blank)
            {
                attack.push_back(toCoord(location.x, location.y+1));

                // Moving forward 2 from the second rank
                if(location.y==1 && board.board[location.x][location.y+2].what_piece==blank)
                    attack.push_back(toCoord(location.x, location.y+2));
            }

            // Take to the right
            if(board.board[location.x+1][location.y+1].what_piece!=blank && board.board[location.x+1][location.y+1].side==black && location.x<7)
                attack.push_back(toCoord(location.x+1, location.y+1));

            // Take to the left
            if(board.board[location.x-1][location.y+1].what_piece!=blank && board.board[location.x-1][location.y+1].side==black && location.y>0)
                attack.push_back(toCoord(location.x-1, location.y+1));

            //
            // Insert En Passant
            //

        }
        break;
    default:
        return;
    }

    return;
}
