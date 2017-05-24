// Contains functions that deal with move generation

#include "movegen.h"

bool compareByScore(const eval_pair &a, const eval_pair &b)
{
    return a.score < b.score;
}

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
    int* move_variaiton = NULL;
    depth_search(n, 6, 0, side, 0, true, move_variaiton);
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

void depth_search(node *parent, int ply, int current_ply, colour side, int highest, bool first, int* move_variation)
{
    Board original = parent->container;
    // declares a node
    node *n;
    colour next_colour;

    // determines the next colour being used
    if(side == white)
        next_colour = black;
    else
        next_colour = white;

    vector <eval_pair> order_of_move;
    eval_pair buff_pair;
    int current_highest = highest;

    if(!first)
    {
        //creates new node
        n = new node;

        // If it's not the first then it creates a new node and adds it to the parent nodes branches.
        parent->branches.push_back(n);

        // updates the board being used
        n->container = parent->container;
        n->trunk = parent;
    }
    else
    {
        // sets the first node to the parent
        n = parent;

        // Creates a new array which is the combination of moves that the search calculates
        move_variation = new int[ply];
        // resets elements
        //for(int i = 0; i < ply; i++)
            //move_variation[i] = noMove;
    }

    // If it reaches the max depth stop
    if(ply == current_ply)
    {
        n->container.bestMove = move_variation[0];
        return;
    }
    n->container.calcBoard(side);
    n->container.calcMoves(next_colour);

    // creates a buff board where moves can be done
    Board *buff_board = &(n->container);

    /*for(int i = 0; i < n->container.moves.size(); i++)
    {
        convert(n->container.moves[i].start_loc);
        cout<<" to ";
        convert(n->container.moves[i].end_loc);
        cout<<endl;
    }*/

    // Go through all the moves and calculate which has the best score.
    for(unsigned int i = 0; i < buff_board->moves.size(); i++)
    {
        // does moves, calculates and evaluates.
        buff_board->do_move(buff_board->moves[i]);
        buff_board->calcBoard((colour)(!(bool)side));
        buff_board->calcMoves(side);
        //cout<<buff_board;
        buff_board->evalBoard();
        cout<<"Score = "<<buff_board->score<<endl;

        // Saves each move done with it's eval score into a vector
        buff_pair.curr_move = buff_board->moves[i];
        buff_pair.score = buff_board->score;
        order_of_move.push_back(buff_pair);
        *buff_board = original;
        buff_board->calcBoard((colour)(!(bool)side));
        buff_board->calcMoves(side);
    }

    // sorts it from lowest to highest score
    std::sort(order_of_move.begin(), order_of_move.end(), compareByScore);

    cout<<"size of order_of_move = "<<order_of_move.size()<<endl;

    for(unsigned int i = 0; i < order_of_move.size(); i++)
    {
        convert(order_of_move[i].curr_move.start_loc);
        cout<<" to ";
        convert(order_of_move[i].curr_move.end_loc);
        cout<<endl;
        cout<<"Score = "<<order_of_move[i].score<<endl;
    }

    // if the highest score is smaller than the max score found, then goes back
    if(order_of_move[order_of_move.size() - 1].score < current_highest)
        return;

    // If it finds a better move it calculates that move instead.
    else if(first)
    {
        for(unsigned int i = 0; i < buff_board->moves.size(); i ++)
        {
            if(buff_board->moves[i] == order_of_move[order_of_move.size()-1].curr_move)
                move_variation[0] = i;
        }
    }
    else
        current_highest = order_of_move[order_of_move.size()-1].score;
    n->container.do_move(order_of_move[order_of_move.size()-1].curr_move);
    cout<<n->container<<endl;
    depth_search(n, ply + 1, current_ply, next_colour, current_highest, false, move_variation);
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
