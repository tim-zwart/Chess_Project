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
extern int countSearches;

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
    if(!(thisMove == noMove) && depth && !searchDeeper && (b.board[thisMove.end_loc.x][thisMove.end_loc.y].what_piece != blank || b.check[white] || b.check[black]))
        searchDeeper = true;

    // Do move and then calculate control for the other side
    b.do_move(thisMove);

    if(thisMove == noMove)
        b.calculate(calcSide);

    // Find other colour
    colour other = (colour)!(bool)calcSide;

    if(b.check[other])
        return illegal;

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
            if(depth == true && currPly == 0)
                cout << i << endl;

            int moveScore = breadth_search(b, maxPly, currPly+1, b.moves[i], other, 0, depth, searchDeeper);

            /*if(b.kingCastle[calcSide])
                cout<<"cool kids"<<endl;*/
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
        assert(bestScore >=-1000000 && bestScore <= 100000);
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
gameState compMove(colour side, Board &b)
{
    /*calculate(side);
    int this_move = rand() % moves.size();
    do_move(moves[this_move]);*/

    // Search through all possibilities a certain number of moves deep
    move_store chosenMove;
    int state = breadth_search(b, 2, 0, noMove, side, &chosenMove, true, false);

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
    b.do_move(chosenMove);

    return continuing;
}

gameState getMove(colour side, Board &b)
{
    move_store nothing;
    // Search through all possibilities a certain number of moves deep
    //int state = breadth_search(n, 2, 0, noMove, side, true);
    int state = breadth_search(b, 2, 0, noMove, side, /* we don't want a move*/ &nothing, false, false);

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

        // Calculate moves
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
                    b.do_move(convert(start_coord, end_coord));
                    return continuing;
                }

            }
        }

        // Error statement if move is not valid
        cout << "That is not a valid move" << endl;
    }
}

int depth_search(Board b, int ply, int current_ply, colour side, move_store thisMove)
{
    // Find the colour that is moving next turn
    colour next_colour = (colour)!(bool)side;

    // Do the move that it has been instructed to
    b.do_move(thisMove);

    if(thisMove == noMove)
        b.calculate(side);

    // If the opponent's king can be taken after their move, return that the move is illegal
    if(b.check[next_colour])
        return illegal;

    // If it reaches the max depth stop
    if(ply == current_ply)
    {
        return breadth_search(b, 2, 0, noMove, side, 0, false, false);
    }

    vector <buff_pair> pairs;
    bool possibleToMove = false;

    // Find the score for every move
    for(unsigned int i=0; i<b.moves.size(); i++)
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
/*
    if(board[m.end_loc.x][m.end_loc.y].castle)
        board[m.end_loc.x][m.end_loc.y].castle=false;
*//*
    // If the piece could castle before, make it so that it can't any more
    if(board[m.end_loc.x][m.end_loc.y].castle)
        board[m.end_loc.x][m.end_loc.y].castle=false;
*/
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
    calculate((colour)!(board[m.end_loc.x][m.end_loc.y].side));
    enpassant.x = -32;
    enpassant.y = -32;
}
