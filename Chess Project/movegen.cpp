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
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
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

