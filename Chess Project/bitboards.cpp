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

void moves(pieces &piece, pieceBoard board)
{
    switch(piece.what_piece)
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
        if(piece.side==black)
        {
            // Moving forward
            if(board.board[piece.location.x][piece.location.y-1].what_piece==blank)
            {
                piece.attack.push_back(toCoord(piece.location.x, piece.location.y-1));

                // Moving forward 2 from the seventh rank
                if(piece.location.y==6 && board.board[piece.location.x][piece.location.y-2].what_piece==blank)
                    piece.attack.push_back(toCoord(piece.location.x, piece.location.y-2));
            }

            // Take to the right
            if(board.board[piece.location.x+1][piece.location.y-1].what_piece!=blank && board.board[piece.location.x+1][piece.location.y-1].side==white && piece.location.x<7)
                piece.attack.push_back(toCoord(piece.location.x+1, piece.location.y-1));

            // Take to the left
            if(board.board[piece.location.x-1][piece.location.y-1].what_piece!=blank && board.board[piece.location.x-1][piece.location.y-1].side==white && piece.location.x>0)
                piece.attack.push_back(toCoord(piece.location.x-1, piece.location.y-1));

            //
            // Insert En Passant
            //
        }

        // If the pawn is white
        if(piece.side==white)
        {
            // Move forward
            if(board.board[piece.location.x][piece.location.y+1].what_piece==blank)
            {
                piece.attack.push_back(toCoord(piece.location.x, piece.location.y+1));

                // Moving forward 2 from the second rank
                if(piece.location.y==1 && board.board[piece.location.x][piece.location.y+2].what_piece==blank)
                    piece.attack.push_back(toCoord(piece.location.x, piece.location.y+2));
            }

            // Take to the right
            if(board.board[piece.location.x+1][piece.location.y+1].what_piece!=blank && board.board[piece.location.x+1][piece.location.y+1].side==black && piece.location.x<7)
                piece.attack.push_back(toCoord(piece.location.x+1, piece.location.y+1));

            // Take to the left
            if(board.board[piece.location.x-1][piece.location.y+1].what_piece!=blank && board.board[piece.location.x-1][piece.location.y+1].side==black && piece.location.y>0)
                piece.attack.push_back(toCoord(piece.location.x-1, piece.location.y+1));

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
