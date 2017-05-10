// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<attacked> avec;
/*
generate_move(Board Board, colour which_colour)
{

    avec attack_loc[8][8];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(Board.board[i][j].attack_option.attack_coord.size() != 0)
            {
                for(int t = 0; t < Board.board[i][j].attack_option.attack_coord.size(); t++)
                    attack_loc[i][j].attack_option.attack_coord;
            }

        }
    }

}
*/
void Board::calcMoves(colour side)
{
    // Check all squares
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
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
    }
}

void breadth_search(colour start_side, int ply)
{

}

void Board::do_move(coord start_loc, coord end_loc)
{
    board[end_loc.x][end_loc.y] = board[start_loc.x][start_loc.y];
    board[start_loc.x][start_loc.y].piece_clear();
}
