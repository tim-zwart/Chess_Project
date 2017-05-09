// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<attacked> avec;
typedef vector<coord> cvec;

void Board::calcMoves(colour side)
{
    // Check all squares
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
<<<<<<< HEAD
            board[i][j].moves(*this);
=======
        {
            // If the piece is the right colour, calculate moves for piece
            if(board[i][j].side==side)
            {
                if(side==white)
                    board[i][j].moves(*this);
                else
                    board[i][j].moves(*this);
            }
        }
>>>>>>> refs/remotes/origin/master
    }
}

void Board::do_move(coord start_loc, coord end_loc)
{
    board[end_loc.x][end_loc.y] = board[start_loc.x][start_loc.y];
    board[start_loc.x][start_loc.y].piece_clear();
}
