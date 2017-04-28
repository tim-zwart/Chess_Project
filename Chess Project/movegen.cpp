// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<Piece> pvec;

generate_move(pieceBoard Board, colour which_colour)
{
    pvec attack_loc[8][8];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(pieceBoard.board[i][j].attack_option.attack_coord.size() != 0)
            {
                for(int t = 0; t < pieceBoard.board[i][j].attack_option.attack_coord.size(); t++)
                    attack_loc[pieceBoard.board[i][j].attack_option.attack_coord[t].x][pieceBoard.board[i][j].attack_option.attack_coord[t].y].push_back(pieceBoard.board[i][j]);
            }

        }
    }
}
