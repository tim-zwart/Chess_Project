// Contains functions that deal with move generation

#include "movegen.h"

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

int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first)
{
    node *n;
    if(!first)
    {
        n = new node;
        parent->branches.push_back(n);
        n->container = parent->container;
        n->trunk = parent;
    }
    else
        n = parent;

    Board *b = &(n->container);

    // Find other colour
    colour other;
    if(calcSide==white)
        other=black;
    else if (calcSide==black)
        other=white;

    // Do move and then calculate control for the other side
    b->do_move(thisMove);

    // Calculate and do next move
    if(maxPly != currPly)
    {
        // Calculate other sides control board and all possible moves
        b->calcBoard(other);
        b->calcMoves(calcSide);

        int bestScore = bool(calcSide)*5000-2500;

        n->branches.clear();

        // Check all possible moves
        for(int i=0; i<(int)b->moves.size(); i++)
        {
            int moveScore = breadth_search(n, maxPly, currPly+1, b->moves[i], colour(bool(other) || first), false);

            if(abs(moveScore)>500)
                continue;

            if(!(bool)calcSide)
            {
                if(moveScore >= bestScore)
                {
                    b->bestMove = i;
                    bestScore = moveScore;
                }
            }
            else if(moveScore <= bestScore)
            {
                b->bestMove = i;
                bestScore = moveScore;
            }
        }
        return bestScore;
    }

    else
    {
        b->evalBoard();
        return b->score;
        //if(b->score != 0)
        //cout << *b << endl;
    }
    // Analyze and return

}

void compMove(colour side, node *&n)
{
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/
    breadth_search(n, 2, 0, noMove, side, true);

    n = n->branches[n->container.bestMove];
}

void getMove(colour side, node *&n)
{
    // Declare variables
    coord end_coord;
    coord start_coord;

    // Go through until a valid move is found
    while(true)
    {
        string start_loc;
        string end_loc;

        // Ask for input
        cout << "Enter the starting location of the piece" << endl;

        // Get input
        while(true)
        {
            cin >> start_loc;
            start_coord = convert(start_loc);
            if(start_coord.x + start_coord.y < 0)
                cout << "Invalid input Try again" << endl;
            else break;
        }

        // Ask for input
        cout << "Enter the ending location of the piece" << endl;

        // Get input
        while(true)
        {
            cin >> end_loc;
            end_coord = convert(end_loc);
            if(end_coord.x + end_coord.y < 0)
                cout << "Invalid input Try again" << endl;
            else break;
        }

        // Calculate opponents control board
        if(side == white)
            n->container.calcBoard(black);
        else if(side == black)
            n->container.calcBoard(white);

        // Calculate moves
        n->container.calcMoves(side);

        // Ensure user inputted move is valid
        for(int i=0; i<(int)n->container.moves.size(); i++)
        {
            if((move_store)n->container.moves[i]==convert(start_coord, end_coord))
            {
                breadth_search(n, 1, 0, noMove, side, true);
                n = n->branches[i];
                return;
            }
        }

        // Error statement if move is not valid
        cout << "Invalid move Try again" << endl;
    }
}

void depth_search(Board& input_board, int ply, int current_ply, colour side, Board& start_board)
{
    if(current_ply == ply)
        return;
    move_store current_it;
    vector<move_store> good_moves;
    int highest_score = -100000;
    for(int i = 0; i < input_board.moves.size(); i++)
    vector <move_store> current_var;
    for(int i = 0; i < (int)input_board.moves.size(); i++)
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
        depth_search(input_board, ply, current_ply + 1, (colour)!(bool)side, start_board);
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
