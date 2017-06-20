// Contains functions that deal with move generation

#include "movegen.h"

/// Functions for struct sorting
// To sort from highest eval first
bool highestFirst(const buff_pair &a, const buff_pair &b)
{
    return a.score > b.score;
}
// To sort from lowest eval first
bool lowestFirst(const buff_pair &a, const buff_pair &b)
{
    return a.score < b.score;
}

/** \brief Calculates the move for the state of the board
 *
 * \param Side that you want to calculate
 */
void Board::calculate(colour side)
{
    // Clear previous moves
    moves.resize(0);

    // Reset checks
    check[white] = false;
    check[black] = false;

    Piece storeKing;

    // Check all squares for pieces
    for (int x=0; x<8; x++)
    {
        for (int y=0; y<8; y++)
        {
            // If the piece is the right colour, calculate moves for piece
            if(board[x][y].what_piece != blank)
            {
                if(board[x][y].what_piece == king)
                {
                    if(board[x][y].side == side)
                        storeKing = board[x][y];
                }
                else
                    board[x][y].moves(*this, board[x][y].side == side);
            }
        }
    }

    storeKing.moves(*this, true);
}

extern int countSearches;

void assert(bool f)
{
    if (!f)
    {
        cout << "SOMETHING BROKE!!!!!!" << endl;
        //__asm int 3;
    }
}

// Breadth first search function, given a ply calculates all moves up untill that ply
int breadth_search(Board b, int maxPly, int currPly, move_store thisMove, colour calcSide, move_store* pickedMove, bool depth, bool searchDeeper)
{
    bool capture = b.board[thisMove.end_loc.x][thisMove.end_loc.y].what_piece != blank;

    // Do move and then calculate control for the other side
    b.do_move(thisMove, currPly != maxPly);
    /*
        if(currPly == 2)
            cout << (int)(!(thisMove == noMove)) << depth << !searchDeeper << (int)(capture) << b.check[white] << b.check[black] << endl;
    */
    if((!(thisMove == noMove)) && depth && !searchDeeper && (capture || b.check[white] || b.check[black]))
        searchDeeper = true;

    if(thisMove == noMove)
        b.calculate(calcSide);

    // Find other colour
    colour other = (colour)!(bool)calcSide;

    if(b.check[other])
        return illegal;

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

        if(depth == true && currPly == 0)
            cout << b.moves.size() << endl;

        // Check all possible moves
        for(int i=0; i<(int)b.moves.size(); i++)
        {
            /*if(i == 19 && currPly == 1)
            {
                cout << b << endl;
            }*/
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
            if(b.check[calcSide])
                return checkmate;
            else
                return stalemate;
        }

        if(pickedMove)
        {
            // If this is the first search and the caller
            *pickedMove = b.moves[b.bestMove];
        }
        assert(bestScore >=-1000000 && bestScore <= 1000000);
        return bestScore;
    }
    else
    {
        if (depth && searchDeeper)
        {
            int ret = depth_search(b, 2, 0, calcSide, noMove);
            assert(ret >= -100000 && ret <= 100000);
            return ret;
        }
        else
        {
            b.evalBoard();
            assert(b.score >= -1000000 && b.score <= 1000000);
            return b.score;
        }
    }
    // Analyze and return
    assert(false);
}
<<<<<<< HEAD

// Creates the move from the computer
gameState compMove(colour side, Board &b)
=======
gameState compMove(colour side, Board &b, vector<move_history> &history)
>>>>>>> refs/remotes/origin/master
{
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/
<<<<<<< HEAD
<<<<<<< HEAD
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

>>>>>>> origin/huck_branch
=======

    bool depth = false;

    if(history.size()>0)
    {
        depth = history[history.size()-1].check || history[history.size()-1].capture;

        if(!depth && history.size() > 1)
            depth = history[history.size()-2].capture || history[history.size()-2].check;
    }

>>>>>>> refs/remotes/origin/master
    // Search through all possibilities a certain number of moves deep
    move_store chosenMove;
    int state = breadth_search(b, 2, 0, noMove, side, &chosenMove, true, depth);

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
    /*
        vector<move_store> moves;
        depth_search(n, 13, 0, side, 0, 0, true, moves);
        n->container.do_move(moves[0]);
    */
    // Move to add to history
    move_history temp;

    // Set move
    temp.thisMove = chosenMove;

    // Check for capture
    temp.capture = b.board[chosenMove.end_loc.x][chosenMove.end_loc.y].what_piece != blank;

    // Do move
    b.do_move(chosenMove, false);

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
>>>>>>> origin/huck_branch
    return continuing;
}

// Gets the moves from the search functions
gameState getMove(colour side, Board &b)
=======
    // Check for check
    temp.check = b.check[!side];

    // Add move to history
    history.push_back(temp);

    return continuing;
}

gameState getMove(colour side, Board &b, vector<move_history> &history)
>>>>>>> refs/remotes/origin/master
{
    move_store nothing;

    // Search through all possibilities a certain number of moves deep

    //int state = breadth_search(n, 2, 0, noMove, side, true);
    int state = breadth_search(b, 2, 0, noMove, side, &nothing, false, false);

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
            else if(b.board[start_coord.x][start_coord.y].side != side)
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

        // Calculate moves for the given side
        b.calculate(side);

        // Ensure user inputted move is valid
        for(int i=0; i<(int)b.moves.size(); i++)
        {
            if((move_store)b.moves[i]==convert(start_coord, end_coord))
            {
                // Search through all possibilities a certain number of moves deep to ensure that the move is legal
                state = breadth_search(b, 2, 0, convert(start_coord, end_coord), (colour)!(bool)side, 0, false, false);
                if(state != illegal)
                {
                    // Move to add to history
                    move_history temp;

                    // Set move
                    temp.thisMove = convert(start_coord, end_coord);

                    // Check for capture
                    temp.capture = b.board[end_coord.x][end_coord.y].what_piece != blank;

                    b.do_move(convert(start_coord, end_coord), true);

                    // Check for check
                    temp.check = b.check[!side];

                    // Add move to history
                    history.push_back(temp);

                    return continuing;
                }
            }
        }

        // Error statement if move is not valid
        cout << "That is not a valid move" << endl;
    }
}

// Depth first search function, given a maximum ply, finds moves using a heuristic up to that ply
int depth_search(Board b, int ply, int current_ply, colour side, move_store thisMove)
{
    // Find the colour that is moving next turn
    colour next_colour = (colour)!(bool)side;

    // Do the move that it has been instructed to
    b.do_move(thisMove, ply != current_ply);

    // If there is no move to start with, happens on first iteration
    if(thisMove == noMove)
        b.calculate(side);

    // If the opponent's king can be taken after their move, return that the move is illegal
    if(b.check[next_colour])
        return illegal;

    // If it reaches the max depth stop
    if(ply == current_ply)
<<<<<<< HEAD
        return;
<<<<<<< HEAD
=======

<<<<<<< HEAD
>>>>>>> origin/huck_branch
    n->container.calcMoves(side);
=======
    if(first)
=======
>>>>>>> origin/huck_branch
    {
        return breadth_search(b, 2, 0, noMove, side, 0, false, false);
    }
<<<<<<< HEAD
>>>>>>> refs/remotes/origin/master

    // creates a buff board where moves can be done
    Board *buff_board = &(n->container);
    Board action_board = original;
    vector <move_store> current_var;

<<<<<<< HEAD
<<<<<<< HEAD
    /*for(int i = 0; i < n->container.moves.size(); i++)
=======
    for(int i = 0; i < n->container.moves.size(); i++)
>>>>>>> origin/huck_branch
=======
    for(unsigned int i = 0; i < n->container.moves.size(); i++)
>>>>>>> refs/remotes/origin/master
=======

    vector <buff_pair> pairs;
    bool possibleToMove = false;

    // Find the score for every move
    for(unsigned int i=0; i<b.moves.size(); i++)
>>>>>>> origin/huck_branch
    {
        buff_pair temp;
        temp.thisMove = b.moves[i];
        temp.score = breadth_search(b, 2, 0, b.moves[i], next_colour, 0, false, false);
        if(temp.score != illegal)
        {
            if(temp.score == checkmate)
                temp.score = -2000 * (side - 0.5);

            if(temp.score == stalemate)
                temp.score = 0;

            if(!possibleToMove)
                possibleToMove = true;

            pairs.push_back(temp);
        }
    }

    // Check if it is checkmate or stalemate
    if(!possibleToMove)
    {
        if(b.check[side])
            return checkmate;
        else
            return stalemate;
    }

    // Sort moves according to score
    if(side == white)
        sort(pairs.begin(), pairs.end(), highestFirst);
    else
        sort(pairs.begin(), pairs.end(), lowestFirst);

    int best = 4000 * (side - 0.5);

    // Number of threads to search
    int nThreads = 3;
    for(unsigned int i = 0; i < (unsigned)nThreads && i < pairs.size(); i++)
    {
        int tempScore;
        if(side == white)
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, pairs[i].thisMove);
        else
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, pairs[i].thisMove);

        if(tempScore != (int)illegal)
        {
            if(tempScore == checkmate)
                tempScore = -2000 * (side - 0.5);

            if(tempScore == stalemate)
                tempScore = 0;
        }

        if(side == white)
            best = max(tempScore, best);
        else
            best = min(tempScore, best);
    }
    for(unsigned int i = pairs.size()-1; i >= (unsigned)nThreads && i > pairs.size()-nThreads-1; i--)
    {
        int tempScore;
        if(side == white)
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, pairs[i].thisMove);
        else
            tempScore = depth_search(b, ply, current_ply + 1, next_colour, pairs[i].thisMove);
        if(side == white)
            best = max(tempScore, best);
        else
            best = min(tempScore, best);
    }
    return best;
}


void Board::do_move(move_store m, bool calc)
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
<<<<<<< HEAD
=======
    /*
        if(board[m.end_loc.x][m.end_loc.y].castle)
            board[m.end_loc.x][m.end_loc.y].castle=false;
    *//*
// If the piece could castle before, make it so that it can't any more
if(board[m.end_loc.x][m.end_loc.y].castle)
board[m.end_loc.x][m.end_loc.y].castle=false;
*/
>>>>>>> refs/remotes/origin/master
    // Clear the old square
    board[m.start_loc.x][m.start_loc.y].piece_clear();

    // If the king is castling...
    if(board[m.end_loc.x][m.end_loc.y].what_piece == king && abs(m.start_loc.x - m.end_loc.x) >= 2 &&
            kingCastle[board[m.end_loc.x][m.end_loc.y].side] == true)
    {
        if(m.end_loc.x == 6 && rookCastle[board[m.end_loc.x][m.end_loc.y].side])
        {
            board[5][m.end_loc.y] = board[7][m.end_loc.y];
            board[5][m.end_loc.y].location = toCoord(5, m.end_loc.y);

            // Clear the old square
            board[7][m.end_loc.y].piece_clear();
            //castledKing[board[5][m.end_loc.y].side] = true;
        }
        else if(m.end_loc.x == 2 && rookCastle2[board[m.end_loc.x][m.end_loc.y].side])
        {
            board[3][m.end_loc.y] = board[0][m.end_loc.y];
            board[3][m.end_loc.y].location = toCoord(3, m.end_loc.y);

            // Clear the old square
            board[0][m.end_loc.y].piece_clear();
            //castledKing[board[3][m.end_loc.y].side] = true;
        }
    }
    else
        kingCastle[board[m.end_loc.x][m.end_loc.y].side] = false;

    if(board[m.end_loc.x][m.end_loc.y].what_piece == rook)
    {
        if(m.end_loc.x == 7)
            rookCastle[board[m.end_loc.x][m.end_loc.y].side] = false;
        else if(m.end_loc.x == 0)
            rookCastle2[board[m.end_loc.x][m.end_loc.y].side] = false;
    }

    // Recalculate moves
    if(calc)
        calculate((colour)!(board[m.end_loc.x][m.end_loc.y].side));
    enpassant.x = -32;
    enpassant.y = -32;

}
