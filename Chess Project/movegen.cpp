// Contains functions that deal with move generation

#include "movegen.h"

bool compareByScore(const eval_pair &a, const eval_pair &b)
{
    return a.score < b.score;
}

/** \brief Calculates the move for the state of the board
 *
 * \param Side that you want to calculate
 */

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

/** \brief A function to find all possible moves to a certain depth
 *
 * \param parent node*  The node of the tree that leads into this function
 * \param maxPly int  The maximum depth to go to
 * \param currPly int  The current depth in the search
 * \param thisMove move_store  The move that the function represents
 * \param calcSide colour  The current side that moves are being calculated for
 * \param first bool  Whether this is the first call of the function
 * \return int  Return the score of the current position
 *
 */
int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first)
{
    // Create new node
    node *n;
    if(!first)
    {
        // Ensure that there is enough memory for a node
        n = new (nothrow) node;
        if(n == NULL)
        {
            cout << "ERROR Could not allocate memory" << endl;
        }
        else
        {
            // Set up node
            parent->branches.push_back(n);
            n->container = parent->container;
            n->trunk = parent;
        }
    }
    else
        n = parent;

    Board *b = &(n->container);

    // Do move and then calculate control for the other side
    b->do_move(thisMove);

    // Find other colour
    colour other = (colour)!(bool)calcSide;

    if(first)
    {
        // Calculate moves and control boards
        b->calcMoves(other);
        b->calcBoard(other);
        b->calcMoves(calcSide);
    }

    if(b->w[king] + b->b[king]<2)
        return takeKing;

    // Calculate and do next move
    if(maxPly != currPly)
    {
        int bestScore = bool(calcSide)*50000-25000;

        bool possibleToMove = false;

        // Check all possible moves
        for(int i=0; i<(int)b->moves.size(); i++)
        {
            int moveScore = breadth_search(n, maxPly, currPly+1, b->moves[i], other, false);
            if(moveScore == takeKing)
                return illegal;
            if(moveScore != (int)illegal)
            {
                if(moveScore == checkmate)
                    moveScore = -2000 * (calcSide - 0.5);

                if(moveScore == stalemate)
                    moveScore = 0;

                if(!possibleToMove)
                    possibleToMove = true;

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
        }

        if(!possibleToMove)
        {
            for(int y=0; y<8; y++)
                for(int x=0; x<8; x++)
                    if(b->board[x][y].what_piece == king)
                    {
                        if(calcSide == white)
                        {
                            if(b->blackControl[x][y]>0)
                                return checkmate;
                        }
                        else if(b->whiteControl[x][y]>0)
                            return checkmate;

                        return stalemate;
                    }
        }
        return bestScore;
    }
    else
    {
        b->evalBoard();
        return b->score;
    }
    // Analyze and return

}

gameState compMove(colour side, node *& n)
{
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/
<<<<<<< HEAD
=======

    #if 0
    vector<move_store> moves;
    depth_search(n, 13, 0, side, 0, 0, true, moves);
    convert(moves[0].start_loc);
    cout<<" to ";
    convert(moves[0].end_loc);
    cout<<endl;
    n->container.do_move(moves[0]);
    n->container.evalBoard();
    cout<<"Score is = "<<n->container.score<<endl;

    #endif

    #if 1
>>>>>>> origin/huck_branch
    // Search through all possibilities a certain number of moves deep
    int state = breadth_search(n, 3, 0, noMove, side, true);

    // If the postition is stalemate, the game is a draw
    if(state == stalemate)
        return draw;

    // If the AI has been checkmated, return that it has lost
    else if(state == checkmate)
    {
        if(side == white)
            return blackWins;
        else
            return whiteWins;
    }

    vector<move_store> moves;
    depth_search(n, 13, 0, side, 0, 0, true, moves);
    n->container.do_move(moves[0]);

    // Delete unused nodes
    for(int i=0; i<(int)n->branches.size(); i++)
        if(i != n->container.bestMove)
            destroy(n->branches[i]);

    // Do move
    n = n->branches[n->container.bestMove];

    // Simplify on trunk
    n->trunk->branches.clear();
    n->trunk->branches.push_back(n);


    for(int i=0; i<(int)n->branches.size(); i++)
        destroy(n->branches[i]);

    n->branches.clear();
<<<<<<< HEAD
=======

    return continuing;
    #endif // 0
>>>>>>> origin/huck_branch
}

gameState getMove(colour side, node *& n)
{
    // Search through all possibilities a certain number of moves deep
    int state = breadth_search(n, 2, 0, noMove, side, true);

    // Clear the nodes that were just created
    for(unsigned int i=0; i<n->branches.size(); i++)
        destroy(n->branches[i]);

    // Clear the branches because they are currently pointing to a nonexistent node
    n->branches.clear();

    // If the postition is stalemate, the game is a draw
    if(state == stalemate)
        return draw;

    // If the player has been checkmated, return that they have lost
    else if(state == checkmate)
    {
        if(side == white)
            return blackWins;
        else
            return whiteWins;
    }
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
                // Create and set up new node
                node *newNode = new node;
                newNode->container = n->container;

                newNode->container.do_move(convert(start_coord, end_coord));

                // Search through all possibilities a certain number of moves deep to ensure that the move is legal
                state = breadth_search(newNode, 2, 0, noMove, (colour)!(bool)side, true);

                // Clear the nodes that were just created
                for(unsigned int i=0; i<newNode->branches.size(); i++)
                    destroy(newNode->branches[i]);

                // Clear the branches because they are currently pointing to a nonexistent node
                newNode->branches.clear();

                if(state != 3)
                {
                    n->branches.push_back(newNode);
                    n = newNode;
                    return continuing;
                }
            }
        }

        // Error statement if move is not valid
        cout << "Invalid move Try again" << endl;
    }
}

void depth_search(node *parent, int ply, int current_ply, colour side, int white_score, int black_score, bool first, vector<move_store> &moves)
{
    Board original = parent->container;
    // declares a node
    node *n;
    colour next_colour;
    int score_check;

    // determines the next colour being used
    if(side == white)
    {
        next_colour = black;
        score_check = white_score;
    }
    else
    {
        next_colour = white;
        score_check = black_score;
    }

    vector <eval_pair> order_of_move;
    eval_pair buff_pair;

    if(!first)
    {
        //creates new node
        n = new node;
        /*
        // If it's not the first then it creates a new node and adds it to the parent nodes branches.
        parent->branches.push_back(n);

        // updates the board being used
        n->container = parent->container;
        n->trunk = parent;
        */
    }
    else
    {
        // sets the first node to the parent
        n = parent;
    }

    // If it reaches the max depth stop
    if(ply == current_ply)
        return;
<<<<<<< HEAD
=======

>>>>>>> origin/huck_branch
    n->container.calcMoves(side);

    // creates a buff board where moves can be done
    Board *buff_board = &(n->container);
    Board action_board = original;
    vector <move_store> current_var;

<<<<<<< HEAD
    /*for(int i = 0; i < n->container.moves.size(); i++)
=======
    for(int i = 0; i < n->container.moves.size(); i++)
>>>>>>> origin/huck_branch
    {
        convert(n->container.moves[i].start_loc);
        cout<<" to ";
        convert(n->container.moves[i].end_loc);
        cout<<endl;
    }

    // Go through all the moves and calculate which has the best score.
    for(unsigned int i = 0; i < buff_board->moves.size(); i++)
    {
        // does moves, calculates and evaluates.
        action_board.do_move(buff_board->moves[i]);
        //cout<<buff_board<<endl;
        action_board.calcMoves(side);
        action_board.calcBoard(side);
        action_board.evalBoard();
        //cout<<"Score = "<<buff_board->score<<endl;

        // Saves each move done with it's eval score into a vector
        buff_pair.curr_move = buff_board->moves[i];
        buff_pair.score = action_board.score;
        order_of_move.push_back(buff_pair);

        //Resets the board
        action_board = original;
        //cout<<buff_board<<endl;
    }

    // sorts it from lowest to highest score
    std::sort(order_of_move.begin(), order_of_move.end(), compareByScore);

    //cout<<"size of order_of_move = "<<order_of_move.size()<<endl;

    /*for(unsigned int i = 0; i < order_of_move.size(); i++)
    {
        convert(order_of_move[i].curr_move.start_loc);
        cout<<" to ";
        convert(order_of_move[i].curr_move.end_loc);
        cout<<endl;
        cout<<"Score = "<<order_of_move[i].score<<endl;
    }*/

    // If it finds a better move it calculates that move instead.
    score_check = order_of_move[order_of_move.size() -1].score;

    // if the highest score is smaller than the max score found, then goes back
    if((order_of_move[order_of_move.size()-1].score < score_check  && side == white) || (order_of_move[order_of_move.size()-1].score > score_check  && side == black) )
    {
        moves.pop_back();
        return;
    }

    for(unsigned int i = order_of_move.size() - 1; i >= order_of_move.size() / 4; i--)
    {
        n->container.do_move(order_of_move[i].curr_move);
        moves.push_back(order_of_move[i].curr_move);
        if(side == white)
            depth_search(n, ply, current_ply + 1, next_colour, score_check, black_score, false, moves);
        else
            depth_search(n, ply, current_ply + 1, next_colour, white_score, score_check, false, moves);
        //cout<<n->container;
        n->container = original;
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

    // Recalculate moves and control boards
    calcMoves(board[m.end_loc.x][m.end_loc.y].side);
    calcBoard(board[m.end_loc.x][m.end_loc.y].side);
    calcMoves((colour)(!(bool)board[m.end_loc.x][m.end_loc.y].side));
}
