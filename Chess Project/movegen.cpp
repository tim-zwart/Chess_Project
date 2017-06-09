// Contains functions that deal with move generation

#include "movegen.h"

bool highestFirst(const buff_pair &a, const buff_pair &b)
{
    return a.score > b.score;
}
bool lowestFirst(const buff_pair &a, const buff_pair &b)
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
    //moves.clear();
    moves.resize(0);
    // Check all squares
    for (int x=0; x<8; x++)
    {
        for (int y=0; y<8; y++)
        {
            // If the piece is the right colour, calculate moves for piece
            if(board[x][y].side==side)
            {
                board[x][y].moves(*this);/*
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
                }*/
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
<<<<<<< HEAD
 extern int countSearches;

 /*
int breadth_search(node *parent, int maxPly, int currPly, move_store thisMove, colour calcSide, bool first)
{countSearches++;
if(countSearches % 1000 == 0)
    cout << "countSearches: " << countSearches << endl;
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
=======
>>>>>>> refs/remotes/origin/master

void assert(bool f)
{
    if (!f)
    {
        cout << "SOMETHING BROKE!!!!!!" << endl;
        //__asm int 3;
    }
}

int breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, move_store* pickedMove, bool depth, bool searchDeeper)
{
    if(!(thisMove == noMove) && depth && !searchDeeper && b.board[thisMove.end_loc.x][thisMove.end_loc.y].what_piece != blank)
        searchDeeper = true;

    // Do move and then calculate control for the other side
    b.do_move(thisMove);

    // Find other colour
    colour other = (colour)!(bool)calcSide;

    if(pickedMove != 0)
    {
        // this means we're on the first level, and they care about the move we return
        // Calculate moves and control boards
        b.calcMoves(other);
        b.calcBoard(other);
        b.calcMoves(calcSide);
    }

    if (b.w[king] + b.b[king] < 2)
    {
        assert(takeKing >= 0 && takeKing <= 100000);
        return takeKing;
    }

    // Calculate and do next move
    if(maxPly != currPly)
    {
        int bestScore = bool(calcSide)*50000-25000;

        bool possibleToMove = false;

        // Check all possible moves
        if(depth == true && currPly == 0)
            cout << b.moves.size() << endl;
        for(int i=0; i<(int)b.moves.size(); i++)
        {
            if(depth == true && currPly == 0)
                cout << i << endl;

            int moveScore = breadth_search(b, maxPly, currPly+1, b.moves[i], other, 0, depth, searchDeeper);
            if (moveScore == takeKing)
            {

                assert(illegal >= 0 && illegal <= 100000);
                return illegal;
            }
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
                        b.bestMove = i;
                        bestScore = moveScore;
                    }
                }
                else if(moveScore <= bestScore)
                {
                    b.bestMove = i;
                    bestScore = moveScore;
                }
            }
            else if(depth && !searchDeeper)
                searchDeeper = true;
        }

        if(!possibleToMove)
        {
            for(int y=0; y<8; y++)
                for(int x=0; x<8; x++)
                    if(b.board[x][y].what_piece == king && b.board[x][y].side == calcSide)
                    {
                        if(calcSide == white)
                        {
                            if (b.blackControl[x][y] > 0)
                            {
                                assert(checkmate >= 0 && checkmate <= 100000);
                                return checkmate;
                            }
                        }
                        else if (b.whiteControl[x][y] > 0)
                        {
                            assert(checkmate >= 0 && checkmate <= 100000);
                            return checkmate;
                        }

                        assert(stalemate >= 0 && stalemate <= 100000);
                        return stalemate;
                    }
        }

        if(pickedMove)
        {
            // If this is the first search and the caller
            *pickedMove = b.moves[b.bestMove];
        }
        assert(bestScore >=-1000000 && bestScore <= 100000);
        return bestScore;
    }
    else
    {
        if (depth && searchDeeper)
        {
            int ret = depth_search(b, 2, 0, calcSide, 0, 0, true, noMove);
            assert(ret >= -100000 && ret <= 100000);
            return ret;
        }
        else
        {
            b.evalBoard();
            assert(b.score >= -100000 && b.score <= 100000);
            return b.score;
        }
    }
    // Analyze and return
    assert(false);
}
gameState compMove(colour side, node *& n)
{
<<<<<<< HEAD
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/
<<<<<<< HEAD
=======

    #define breadth 1

    #if !breadth
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

<<<<<<< HEAD
    #if 1
>>>>>>> origin/huck_branch
=======
    #if breadth
>>>>>>> refs/remotes/origin/master
=======
>>>>>>> refs/remotes/origin/master
    // Search through all possibilities a certain number of moves deep
    move_store chosenMove;
    int state = breadth_search(n->container, 3, 0, noMove, side, &chosenMove, true, false);

    // If the postition is stalemate, the game is a draw
    if(state == stalemate)
        return draw;

    // If the position is checkmate, return that it is
    else if(state == checkmate)
    {
        if(side == white)
            return blackWins;
        else
            return whiteWins;
    }

<<<<<<< HEAD
    vector<move_store> moves;
    depth_search(n, 13, 0, side, 0, 0, true, moves);
    n->container.do_move(moves[0]);

=======
    node *newNode = new node;
    newNode->trunk = n;
    newNode->container = n->container;
    newNode->container.do_move(chosenMove);
    n->branches.push_back(newNode);
    n = newNode;
<<<<<<< HEAD
/*
>>>>>>> refs/remotes/origin/master
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
<<<<<<< HEAD
=======

=======
*/
>>>>>>> refs/remotes/origin/master
    return continuing;
    #endif // 0
>>>>>>> origin/huck_branch
=======

    return continuing;
>>>>>>> refs/remotes/origin/master
}

gameState getMove(colour side, node *& n)
{
    move_store nothing;
    // Search through all possibilities a certain number of moves deep
    //int state = breadth_search(n, 2, 0, noMove, side, true);
    int state = breadth_search(n->container, 2, 0, noMove, side, /* we don't want a move*/ &nothing, false, false);

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
            if(start_loc == "abort")
                return end_game;
            start_coord = convert(start_loc);
            if(start_coord.x + start_coord.y < 0)
                cout << "Invalid input" << endl;
            else if(n->container.board[start_coord.x][start_coord.y].side != side)
                cout << "There is no piece at that location" << endl;
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
                cout << "Invalid input" << endl;
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
                state = breadth_search(newNode->container, 2, 0, noMove, (colour)!(bool)side, 0, false, false);

                if(state != 3)
                {
                    n->branches.push_back(newNode);
                    n = newNode;
                    return continuing;
                }
            }
        }

        // Error statement if move is not valid
        cout << "That is not a valid move" << endl;
    }
}

int depth_search(Board b, int ply, int current_ply, colour side, int white_score, int black_score, bool first, move_store thisMove)
{
    /*
       // declares a node
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
       }*/

    colour next_colour = (colour)!(bool)side;
    b.do_move(thisMove);
    if(first)
    {
        b.calcMoves(next_colour);
        b.calcBoard(next_colour);
        b.calcMoves(side);
    }
    /*vector <eval_pair> order_of_move;
    eval_pair buff_pair;*/

    // If it reaches the max depth stop

    if(ply == current_ply)
    {
        return breadth_search(b, 1, 0, noMove, side, 0, false, false);
    }

    vector <buff_pair> pairs;
    bool possibleToMove = false;
    for(int i=0; i<b.moves.size(); i++)
    {
        buff_pair temp;
        temp.thisMove = b.moves[i];
        temp.score = breadth_search(b, 2, 0, b.moves[i], next_colour, 0, false, false);
        if(temp.score != (int)illegal)
        {
            if(temp.score == checkmate)
                temp.score = -2000 * (side - 0.5);

            if(temp.score == stalemate)
                temp.score = 0;

<<<<<<< HEAD
    // If it reaches the max depth stop
    if(ply == current_ply)
        return;
<<<<<<< HEAD
=======

<<<<<<< HEAD
>>>>>>> origin/huck_branch
    n->container.calcMoves(side);
=======
    if(first)
    {
        // Calculate moves and control boards
        n->container.calcMoves(next_colour);
        n->container.calcBoard(next_colour);
        n->container.calcMoves(side);
    }
>>>>>>> refs/remotes/origin/master
=======
            if(!possibleToMove)
                possibleToMove = true;

            pairs.push_back(temp);
        }
    }
    if(!possibleToMove)
        cout << "Can't move" << endl;
>>>>>>> refs/remotes/origin/master

    if(side == white)
        sort(pairs.begin(), pairs.end(), highestFirst);
    else
        sort(pairs.begin(), pairs.end(), lowestFirst);

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    /*for(int i = 0; i < n->container.moves.size(); i++)
=======
    for(int i = 0; i < n->container.moves.size(); i++)
>>>>>>> origin/huck_branch
=======
    for(unsigned int i = 0; i < n->container.moves.size(); i++)
>>>>>>> refs/remotes/origin/master
    {
        convert(n->container.moves[i].start_loc);
        cout<<" to ";
        convert(n->container.moves[i].end_loc);
        cout<<endl;
    }
=======
>>>>>>> refs/remotes/origin/master

    /*
        Board action_board = b;
        action_board.do_move(thisMove);

        if(thisMove == noMove)
        {
            // Calculate moves and control boards
            b.calcMoves(next_colour);
            b.calcBoard(next_colour);
            b.calcMoves(side);

        }

        // creates a buff board where moves can be done
        vector <move_store> current_var;

        /*for(unsigned int i = 0; i < b.moves.size(); i++)
        {
            convert(b.moves[i].start_loc);
            cout<<" to ";
            convert(b.moves[i].end_loc);
            cout<<endl;
        }*/
    /*
    // Go through all the moves and calculate which has the best score.
    for(unsigned int i = 0; i < action_board.moves.size(); i++)
    {
        action_board.calcMoves(next_colour);
        action_board.calcBoard(next_colour);
        action_board.calcMoves(side);
        // does moves, calculates and evaluates.
        action_board.do_move(action_board.moves[i]);
        action_board.evalBoard();

        //action_board.score = breadth_search();
        //cout<<"Score = "<<buff_board->score<<endl;

        // Saves each move done with it's eval score into a vector
        buff_pair.curr_move = action_board.moves[i];
        buff_pair.score = action_board.score;
        order_of_move.push_back(buff_pair);

        //Resets the board
        action_board = b;
        //cout<<*buff_board<<endl;
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

    //cout<<"Test size = "<<order_of_move.size()<<endl<<"currentPly: "<<current_ply<<endl;;
    // If it finds a better move it calculates that move instead.
    //score_check = order_of_move[order_of_move.size() -1].score;

    // if the highest score is smaller than the max score found, then goes back
    /*if((order_of_move[order_of_move.size()-1].score < score_check  && side == white) || (order_of_move[order_of_move.size()-1].score > score_check  && side == black) )
    {
        return 0;
    }

    for(unsigned int i = order_of_move.size() - 1; i >= (order_of_move.size()-1) / 1.001; i--)
    {
        if(side == white)
            depth_search(b, ply, current_ply + 1, next_colour, score_check, black_score, false, order_of_move[i].curr_move);
        else
            depth_search(b, ply, current_ply + 1, next_colour, white_score, score_check, false, order_of_move[i].curr_move);
        //cout<<n->container;
    }*/
    int score_check=0;
    int best = 4000 * (side - 0.5);
    for(unsigned int i = 0; i < 2 && i < pairs.size(); i++)
    {
        int tempScore;
        if(side == white)
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, score_check, black_score, false, pairs[i].thisMove);
        else
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, white_score, score_check, false, pairs[i].thisMove);
        if(side == white)
            best = max(tempScore, best);
        else
            best = min(tempScore, best);
    }
    return best;
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

    // If the king is castling...
    if(board[m.end_loc.x][m.end_loc.y].what_piece == king && abs(m.start_loc.x - m.end_loc.x) >= 2)
    {
        if(m.end_loc.x == 6)
        {
            board[5][m.end_loc.y] = board[7][m.end_loc.y];
            board[5][m.end_loc.y].location == toCoord(5, m.end_loc.y);

            // Clear the old square
            board[7][m.end_loc.y].piece_clear();
        }
        else
        {
            board[3][m.end_loc.y] = board[0][m.end_loc.y];
            board[3][m.end_loc.y].location = toCoord(3, m.end_loc.y);

            // Clear the old square
            board[0][m.end_loc.y].piece_clear();

        }
    }

    // Recalculate moves and control boards
    calcMoves(board[m.end_loc.x][m.end_loc.y].side);
    calcBoard(board[m.end_loc.x][m.end_loc.y].side);
    calcMoves((colour)(!(bool)board[m.end_loc.x][m.end_loc.y].side));
}
