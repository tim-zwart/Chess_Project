// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

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

void Board::breadth_search(colour start_side, int ply, int current_ply, vector <vector <coord> >& listMoves, Board current_state)
{
    if(current_ply == ply)
        return;
    Board buff_board;
    buff_board = current_state;
    colour next_side;
    for(int i = 0; i < 8; i++)
    {
        for(int t = 0; t < 8; t++)
        {
            if(buff_board.board[i][t].side == start_side)
            {
                for(unsigned int q = 0; q < buff_board.board[i][t].attack_option.attack_coord.size(); q++)
                {
                    buff_board = current_state;
                    buff_board.do_move(toCoord(i, t), buff_board.board[i][t].attack_option.attack_coord[q]);
                    buff_board.calculate(start_side);

                    if(start_side == white)
                        next_side = black;
                    else
                        next_side = white;
                    breadth_search(next_side, ply,current_ply+1,listMoves, buff_board);
                }
                for(unsigned int q = 0; q < buff_board.board[i][t].movement.size(); q++)
                {
                    buff_board = current_state;
                    buff_board.do_move(toCoord(i, t),buff_board.board[i][t].movement[q]);
                    buff_board.calculate(start_side);

                    if(start_side == white)
                        next_side = black;
                    else
                        next_side = white;
                    breadth_search(next_side, ply, current_ply+1, listMoves, buff_board);
                }
            }
        }
    }
}

void Board::depth_search(int ply, int current_ply, colour side)
{
    vector <coordPair> current_coord;
    generate_move(side);
    if(side == black)
        current_coord = black_attack;
    else
        current_coord = white_attack;
}

void Board::do_move(coord start_loc, coord end_loc)
{
    // Set new square to piece
    board[end_loc.x][end_loc.y] = board[start_loc.x][start_loc.y];

    // Update piece location
    board[end_loc.x][end_loc.y].location = end_loc;

    // If the piece could castle before, make it so that it can't any more
    if(board[end_loc.x][end_loc.y].castle)
        board[end_loc.x][end_loc.y].castle=false;

    // Clear the old square
    board[start_loc.x][start_loc.y].piece_clear();
}
