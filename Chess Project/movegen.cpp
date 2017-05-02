// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<attacked> avec;
/*
generate_move(pieceBoard Board, colour which_colour)
{

    avec attack_loc[8][8];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(pieceBoard.board[i][j].attack_option.attack_coord.size() != 0)
            {
                for(int t = 0; t < pieceBoard.board[i][j].attack_option.attack_coord.size(); t++)
                    attack_loc[i][j].attack_option.attack_coord;
            }

        }
    }

}
*/
void calcMoves(pieceBoard &board, bitboard attackBoard, colour side)
{
    vector <int> moves;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if(board.board[i][j].side==side)
                board.board[i][j].moves(board, attackBoard);
        }
    }
}

