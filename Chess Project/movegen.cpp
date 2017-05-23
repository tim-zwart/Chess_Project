// Contains functions that deal with move generation

#include "movegen.h"
#include "bitboards.h"

void Board::calcMoves(colour side)
{
    // Clear previous moves
    moves.clear();

    // Check all squares
    for (int x=0; x<8; x++)
    {
        for (int y=0; y<8; y++)
        {
            // If the piece is the right colour, calculate moves for piece
            if(board[x][y].side==side)
            {
                board[x][y].moves(*this);
                move_store m;
                m.start_loc=board[x][y].location;
                for(int i=0; i<(int) board[x][y].movement.size(); i++)
                {
                    m.end_loc=board[x][y].movement[i];
                    moves.push_back(m);
                }
                //board[x][y].testing();
                for(int i=0; i<(int)board[x][y].attack_option.attack_coord.size(); i++)
                {
                    m.end_loc=board[x][y].attack_option.attack_coord[i];
                    moves.push_back(m);
                }
            }
        }
    }
}

void breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, node *parent)
{
    // Find other colour
    colour other;
    if(calcSide==white)
        other=black;
    else if (calcSide==black)
        other=white;

    // Do move
    b.do_move(thisMove);
    b.calcBoard(other);
    node *n;
    //n->container = &b;
    //n->trunk = parent;
    //parent->branches.push_back(n);


    b.calcMoves(calcSide);
    b.evalBoard();
    // Calculate and do next move
    if(maxPly != currPly)
    {
        for(int i=0; i<(int)b.moves.size(); i++)
        {
            breadth_search(b, maxPly, currPly+1, b.moves[i], other, n);
        }
    }

    else
    {
        if(b.score != 0)
        cout << b << endl;
    }
    // Analyze and return
}

void depth_search(Board& input_board, int ply, int current_ply, colour side, Board& start_board)
{
    if(current_ply == ply)
        return;
    move_store current_it;
    vector<move_store> good_moves;
    int highest_score = -100000;
    for(int i = 0; i < input_board.moves.size(); i++)
    {
        input_board.do_move(input_board.moves[i]);
        input_board.calculate(side);
        input_board.evalBoard();
        if((input_board.score > highest_score) || (highest_score = - 100000))
        {
            current_it = input_board.moves[i];
            current_it.eval = input_board.score;
            highest_score = input_board.score;
        }
    }
    for(int i = 0; i < good_moves.size(); i++)
    {
        depth_search(input_board, ply, current_ply + 1, !(bool)side, start_board);
    }

}

void Board::do_move(move_store m)
{
    if(m.start_loc == m.end_loc)
        return;

    // If a piece is being taken, subtract it from the piece count
    if(board[m.end_loc.x][m.end_loc.y].side==white)
        w[board[m.end_loc.x][m.end_loc.y].what_piece]--;
    else if(board[m.end_loc.x][m.end_loc.y].side==black)
        b[board[m.end_loc.x][m.end_loc.y].what_piece]--;

    // Set new square to piece
    board[m.end_loc.x][m.end_loc.y] = board[m.start_loc.x][m.start_loc.y];

    // Update piece location
    board[m.end_loc.x][m.end_loc.y].location = m.end_loc;

    if(board[m.end_loc.x][m.end_loc.y].castle)
        board[m.end_loc.x][m.end_loc.y].castle=false;

    // If the piece could castle before, make it so that it can't any more
    if(board[m.end_loc.x][m.end_loc.y].castle)
        board[m.end_loc.x][m.end_loc.y].castle=false;

    // Clear the old square
    board[m.start_loc.x][m.start_loc.y].piece_clear();
}

node* create(Board b)
{
    node *n = new node;
    n->container=&b;
    return n;
}
