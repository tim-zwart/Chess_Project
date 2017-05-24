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

    // Find other colour
    colour other;
    if(calcSide==white)
        other=black;
    else if (calcSide==black)
        other=white;

    // Do move and then calculate control for the other side
    b->do_move(thisMove);

    if(b->w[king] + b->b[king]<2)
        return takeKing;

    // Calculate and do next move
    if(maxPly != currPly)
    {
        // Calculate other sides control board and all possible moves
        b->calcBoard(other);
        b->calcMoves(calcSide);

        int bestScore = bool(calcSide)*50000-25000;

        for(int i=0; i<(int)n->branches.size(); i++)
            destroy(n->branches[i]);

        n->branches.clear();

        bool possibleToMove = false;

        // Check all possible moves
        for(int i=0; i<(int)b->moves.size(); i++)
        {
            int moveScore = breadth_search(n, maxPly, currPly+!(bool)first, b->moves[i], colour(bool(other) || first), false);
            if(moveScore == takeKing)
                return illegal;
            if(moveScore != (int)illegal)
            {

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

                        return 0;
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

void compMove(colour side, node *& n)
{
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/

    // Search through all possibilities a certain number of moves deep
    breadth_search(n, 3, 0, noMove, side, true);

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
}

void getMove(colour side, node *& n)
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
                // Create and set up new node
                node *newNode = new node;
                newNode->container = n->container;

                // Store pointer to node
                n->branches.push_back(newNode);

                // Do move in new node
                newNode->container.do_move(n->container.moves[i]);

                // Update the current board
                n = n->branches[0];

                return;
            }

            // Delete unused nodes
            /*for(int i=0; i<(int)n->trunk->branches.size(); i++)
                if(i != n->trunk->container.bestMove)
                    destroy(n->trunk->branches[i]);

            // Simplify on trunk
            n->trunk->branches.clear();
            n->trunk->branches.push_back(n);*/
            //////////////////////////////////////////
            {
                /*breadth_search(n, 1, 0, noMove, side, true);
                n = n->branches[i];

                // Delete unused nodes
                for(int i=0; i<(int)n->trunk->branches.size(); i++)
                    if(i != n->trunk->container.bestMove)
                        destroy(n->trunk->branches[i]);

                // Simplify on trunk
                n->trunk->branches.clear();
                n->trunk->branches.push_back(n);
                return;*/
            }
        }

        // Error statement if move is not valid
        cout << "Invalid move Try again" << endl;
    }
}

void Board::depth_search(int ply, int current_ply, colour side)
{
    move_store current_it;
    vector <move_store> current_var;
    for(int i = 0; i < (int)moves.size(); i++)
    {
        current_it = moves[i];

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
