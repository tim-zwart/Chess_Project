// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

typedef vector<attacked> avec;
<<<<<<< HEAD
typedef vector<coord> cvec;

void calcMoves(pieceBoard &board, bitboard attackBoard, colour side)
=======
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
>>>>>>> refs/remotes/origin/master
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

// Function that moves a piece given the color, start, and end location
// Returns a -1 if it is an invalid move
// Returns a 0 if it is only movement
// Returns a 1-6 if it captures a piece with the piece corresponding to the number
int move_piece( pieceBoard &main_board, coord start, coord endLoc)
{
    int piece_object;
    Piece buffer;
    buffer = main_board.board[start.x][start.y];
    main_board.board[start.x][start.y].piece_clear();
    piece_object = (int)main_board.board[endLoc.x][endLoc.y].what_piece;
    main_board.board[endLoc.x][endLoc.y] = buffer;
    return piece_object;
}

int move_selection(pieceBoard main_board, colour side)
{
    cvec checks;
    cvec capture;
    cvec quiet;

    pieceBoard buffer = main_board;

    all_moves_gen(main_board, side, checks, capture, quiet);

}

void all_moves_gen(pieceBoard Board, colour side, cvec& checks, cvec& capture, cvec& quiet);

