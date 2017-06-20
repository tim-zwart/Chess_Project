// Contains bitboard arguments and related functions

#include "bitboards.h"

ostream & operator<<(ostream & stream, vector<coord> cvec)
{
    cout<<endl;
    for(unsigned int i = 0; i < cvec.size(); i++)
    {
        convert(cvec[i]);
        cout<<" ";
    }
    cout<<endl;
    return stream;
}

// Output Board class
ostream & operator<<(ostream & stream, Board &b)
{
    stream << endl;
    // Go throught the entire board
    for (int i=7; i>=0; i--)
    {
        stream << i+1 << "   ";
        for (int j=0; j<8; j++)
        {
            // Convert to a representation as a character
            char c;
            switch(b.board[j][i].what_piece)
            {
            case king:
                c='K';
                break;
            case queen:
                c='Q';
                break;
            case bishop:
                c='B';
                break;
            case knight:
                c='N';
                break;
            case rook:
                c='R';
                break;
            case pawn:
                c='P';
                break;
            default:
                c='*';
                break;
            }
            // If the piece is black, make the representation lower case
            if(b.board[j][i].side==black)
                c += 32;

            // Output character onto space on board
            stream << c << " ";
        }
        // New line on board
        stream << endl;
    }
    stream << endl << "    a b c d e f g h" << endl;
    return stream;
}

bool operator==(coord first, coord second)
{
    return (first.x == second.x && first.y == second.y);
}

bool operator==(move_store first, move_store second)
{
    return (first.start_loc == second.start_loc && first.end_loc == second.end_loc);
}

coord toCoord(int x, int y)
{
    coord c;
    c.x=x;
    c.y=y;
    return c;
}

// Piece constructor
Piece::Piece()
{
    // Set everything to false / blank
    what_piece = blank;
    side = none;
    dir = 0;
}

// Piece constructor
Piece::Piece(coord l, chess_piece p, colour s)
{
    // Set everything to the input
    location = l;
    what_piece = p;
    side = s;

    // Set direction depending on side
    dir = (side-0.5) * -2;
}

void Piece::moves(Board &board, bool movePiece)
{
    // The depth for rooks and bishops to move
    int distance = 8;

    // The 4 diagonal directions for pieces
    bool tr=true; // Top right
    bool tl=true; // Top left
    bool br=true; // Bottom right
    bool bl=true; // Bottom left

    // The 4 non diagonal directions for pieces
    bool u=true; // Up
    bool d=true; // Down
    bool r=true; // Right
    bool l=true; // Left

    switch(what_piece)
    {
    case king:
        // Go through as if the king was a bishop and a rook but only going one square
        distance = 2;

        if(board.kingCastle[side])
        {
            int y = 3.5-3.5*dir;

            // Queenside castle
            if(board.rookCastle2[side] && board.board[1][y].what_piece==blank
                    && board.board[2][y].what_piece==blank && board.board[3][y].what_piece==blank)
                board.moves.push_back(convert(location, toCoord(2, y)));
            /*
                        // Kingside castle
                        if(board.rookCastle[side])
                            cout << "Rookcastle worked" << endl;
                        if(board.board[6][y].what_piece==blank)
                            cout << "Board[6][8] is blank" << endl;
                        if(board.board[5][y].what_piece==blank)
                            cout << "Board[5][8] is blank" << endl;

                        if(board.rookCastle[side] && board.board[6][y].what_piece==blank
                                && board.board[5][y].what_piece==blank)
                                    board.moves.push_back(convert(location, toCoord(6, y)));
            */
        }
    case queen:
    // Go through as if the queen was a bishop and a rook

    case bishop:
        for (int i=1; i<distance; i++)
        {
            // Top Right
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tr && (location.x+i>7 || location.y+i>7 || board.board[location.x+i][location.y+i].side==side))
                tr=false;
            else if(tr && board.board[location.x+i][location.y+i].side == !side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x+i][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                else if(board.board[location.x+i][location.y+i].side != none)
                {
                    board.moves.push_back(convert(location, toCoord(location.x+i, location.y+i)));
                    if(!board.check[!side] && board.board[location.x+i][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                tr=false;
            }
            else if(movePiece && tr)
                board.moves.push_back(convert(location, toCoord(location.x+i, location.y+i)));

            // Top Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tl && (location.x-i<0 || location.y+i>7 || board.board[location.x-i][location.y+i].side==side))
                tl=false;
            else if(tl && board.board[location.x-i][location.y+i].side == !side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x-i][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                else if(board.board[location.x-i][location.y+i].side != none)
                {
                    board.moves.push_back(convert(location, toCoord(location.x-i, location.y+i)));
                    if(!board.check[!side] && board.board[location.x-i][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                tl=false;
            }
            else if(movePiece && tl)
                board.moves.push_back(convert(location, toCoord(location.x-i, location.y+i)));
            /*
                        // Bottom Right
                        if(br && location.x+i<8 && location.y-i>0)
                            control.push_back(toCoord(location.x+i, location.y-i));
                        // If the position is off of the board or a piece of the same colour is in the way, you can't move there
                        if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                            br=false;
                        else if(br && board.board[location.x+i][location.y-i].side != side && board.board[location.x+i][location.y-i].side != none)
                        {
                            board.moves.push_back(convert(location, toCoord(location.x+i, location.y-i)));
                            //attack_option.which_piece.push_back(board.board[location.x+i][location.y-i].what_piece);
                            br=false;
                        }
                        else if(br)
                            board.moves.push_back(convert(location, toCoord(location.x+i, location.y-i)));

                        // Bottom Left*/
            /*if(bl && location.x-i>=0 && location.y-i>=0)
                control.push_back(toCoord(location.x-i, location.y-i));*/
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there

            if(bl && (location.x-i<0 || location.y-i<0 || board.board[location.x-i][location.y-i].side==side))
                bl=false;
            else if(bl && board.board[location.x-i][location.y-i].side == !side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x-i][location.y-i].what_piece == king)
                        board.check[!side] = true;
                }
                else if(board.board[location.x-i][location.y-i].side != none)
                {
                    board.moves.push_back(convert(location, toCoord(location.x-i, location.y-i)));
                    if(!board.check[!side] && board.board[location.x-i][location.y-i].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                bl=false;
            }
            else if(movePiece && bl)
                board.moves.push_back(convert(location, toCoord(location.x-i, location.y-i)));

            // Bottom Right
            /*if(br && location.x+i<8 && location.y-i>0)
                control.push_back(toCoord(location.x+i, location.y-i));*/
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there

            if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                br=false;
            else if(br && board.board[location.x+i][location.y-i].side == !side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x+i][location.y-i].what_piece == king)
                        board.check[!side] = true;
                }
                else if(board.board[location.x+i][location.y-i].side != none)
                {
                    board.moves.push_back(convert(location, toCoord(location.x+i, location.y-i)));
                    if(!board.check[!side] && board.board[location.x+i][location.y-i].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                br=false;
            }
            else if(movePiece && br)
                board.moves.push_back(convert(location, toCoord(location.x+i, location.y-i)));

            // If the bishop is restricted by pieces in all diagonals, end movement
            if(!tr && !tl && !br && !bl)
                break;
        }
        if(what_piece==bishop)
            break;

    case rook:
        for(int i=1; i<distance; i++)
        {
            // Move Up
            if(u && (location.y+i>7 || board.board[location.x][location.y+i].side == side))
                u=false;
            else if(u && board.board[location.x][location.y+i].what_piece != blank)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                else
                {
                    board.moves.push_back(convert(location, toCoord(location.x, location.y+i)));
                    if(!board.check[!side] && board.board[location.x][location.y+i].what_piece == king)
                        board.check[!side] = true;
                }
                u=false;
            }
            else if (movePiece && u)
                board.moves.push_back(convert(location, toCoord(location.x, location.y+i)));

            // Move Down
            if(d && (location.y-i<0 || board.board[location.x][location.y-i].side == side))
                d=false;
            else if(d && board.board[location.x][location.y-i].what_piece != blank)
            {
            if(!movePiece)
            {
                if(!board.check[!side] && board.board[location.x][location.y-i].what_piece == king)
                    board.check[!side] = true;
            }
            else{
                board.moves.push_back(convert(location, toCoord(location.x, location.y-i)));
                if(!board.check[!side] && board.board[location.x][location.y-i].what_piece == king)
                    board.check[!side] = true;}
                d=false;
            }
            else if (movePiece && d)
                board.moves.push_back(convert(location, toCoord(location.x, location.y-i)));

            // Move Right
            if(r && (location.x+i>7 || board.board[location.x+i][location.y].side == side))
                r=false;
            else if(r && board.board[location.x+i][location.y].what_piece != blank && board.board[location.x+i][location.y].side != side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x+i][location.y].what_piece == king)
                        board.check[!side] = true;
                }
                else
                {
                    board.moves.push_back(convert(location, toCoord(location.x+i, location.y)));
                    if(!board.check[!side] && board.board[location.x+i][location.y].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x+i][location.y].what_piece);
                r=false;
            }
            else if (movePiece && r)
                board.moves.push_back(convert(location, toCoord(location.x+i, location.y)));

            // Move Left
            if(l && (location.x-i<0 || board.board[location.x-i][location.y].side == side))
                l=false;
            else if(l && board.board[location.x-i][location.y].what_piece != blank && board.board[location.x-i][location.y].side != side)
            {
                if(!movePiece)
                {
                    if(!board.check[!side] && board.board[location.x-i][location.y].what_piece == king)
                        board.check[!side] = true;
                }
                else
                {
                    board.moves.push_back(convert(location, toCoord(location.x-i, location.y)));
                    if(!board.check[!side] && board.board[location.x-i][location.y].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x-i][location.y].what_piece);

                l=false;
            }
            else if (movePiece && l)
                board.moves.push_back(convert(location, toCoord(location.x-i, location.y)));


            if(!l && !r && !d && !u)
                break;
        }
        break;

    case knight:

        // Knight Movement for tr, tl, dr, dl
        for(int i = -2; i <= 2; i += 4)
        {
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y + 1 < 8)
            {
                if(board.board[location.x + i][location.y + 1].side != side)
                {
                    if(!movePiece)
                    {
                        if(!board.check[!side] && board.board[location.x+i][location.y+1].what_piece == king)
                            board.check[!side] = true;
                    }
                    //Checks if the location isn't blank
                    else if(board.board[location.x + i][location.y + 1].what_piece != blank)
                    {
                        board.moves.push_back(convert(location, toCoord(location.x + i, location.y + 1)));
                        if(!board.check[!side] && board.board[location.x + i][location.y + 1].what_piece == king)
                            board.check[!side] = true;
                        //attack_option.which_piece.push_back(board.board[location.x + i][location.y + 1].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        board.moves.push_back(convert(location, toCoord(location.x + i, location.y + 1)));
                }
            }

            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y - 1 >= 0)
            {
                //control.push_back(toCoord(location.x + i, location.y - 1));
                if(board.board[location.x + i][location.y - 1].side != side)
                {
                    if(!movePiece)
                    {
                        if(!board.check[!side] && board.board[location.x + i][location.y - 1].what_piece == king)
                            board.check[!side] = true;
                    }
                    //Checks if the location isn't blank
                    else if(board.board[location.x + i][location.y - 1].what_piece != blank)
                    {
                        board.moves.push_back(convert(location, toCoord(location.x + i, location.y - 1)));
                        if(!board.check[!side] && board.board[location.x+i][location.y-1].what_piece == king)
                            board.check[!side] = true;
                        //attack_option.which_piece.push_back(board.board[location.x + i][location.y - 1].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        board.moves.push_back(convert(location, toCoord(location.x + i, location.y - 1)));
                }
            }
            if(location.x + 1 < 8 && location.y + i < 8 && location.y + i >= 0)
            {
                //control.push_back(toCoord(location.x + 1, location.y + i));
                if(board.board[location.x + 1][location.y + i].side != side)
                {
                    if(!movePiece)
                    {
                        if(!board.check[!side] && board.board[location.x + 1][location.y + i].what_piece == king)
                            board.check[!side] = true;
                    }
                    //Checks if the location isn't blank
                    else if(board.board[location.x + 1][location.y + i].what_piece != blank)
                    {
                        board.moves.push_back(convert(location, toCoord(location.x + 1, location.y + i)));
                        if(!board.check[!side] && board.board[location.x+1][location.y+i].what_piece == king)
                            board.check[!side] = true;
                        //attack_option.which_piece.push_back(board.board[location.x + 1][location.y + i].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        board.moves.push_back(convert(location, toCoord(location.x + 1, location.y + i)));
                }
            }
            if(location.x - 1 >= 0 && location.y + i < 8 && location.y + i >= 0)
            {
                //control.push_back(toCoord(location.x - 1, location.y + i));
                if(board.board[location.x - 1][location.y + i].side != side)
                {
                    if(!movePiece)
                    {
                        if(!board.check[!side] && board.board[location.x - 1][location.y + i].what_piece == king)
                            board.check[!side] = true;
                    }
                    //Checks if the location isn't blank
                    else if(board.board[location.x - 1][location.y + i].what_piece != blank)
                    {
                        board.moves.push_back(convert(location, toCoord(location.x - 1, location.y + i)));
                        if(!board.check[!side] && board.board[location.x-1][location.y+i].what_piece == king)
                            board.check[!side] = true;
                        //attack_option.which_piece.push_back(board.board[location.x - 1][location.y + i].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        board.moves.push_back(convert(location, toCoord(location.x - 1, location.y + i)));
                }
            }
        }
        break;

    case pawn:
        // Moves for pawns

        // Moving forward
        if(movePiece && board.board[location.x][location.y+dir].what_piece==blank)
        {
            board.moves.push_back(convert(location, toCoord(location.x, location.y+dir)));

            // Moving forward 2 from the seventh rank
            if(location.y==(3.5-2.5*dir) && board.board[location.x][location.y+2*dir].what_piece==blank)
            {
                board.moves.push_back(convert(location, toCoord(location.x, location.y+2*dir)));
                board.enpassant.x = location.x;
                board.enpassant.y = location.y + (2 * dir);
            }
        }

        // Take to the right
        if(location.x<7)
        {
            //control.push_back(toCoord(location.x+1, location.y+dir));
            if(board.board[location.x+1][location.y+dir].side!=side)
            {
                if(!movePiece && !board.check[!side] && board.board[location.x+1][location.y+dir].what_piece == king)
                    board.check[!side] = true;
                else if(board.board[location.x+1][location.y+dir].what_piece != blank)
                {
                    board.moves.push_back(convert(location, toCoord(location.x+1, location.y+dir)));
                    if(!board.check[!side] && board.board[location.x+1][location.y+dir].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x + 1][location.y+dir].what_piece);
            }
            /*
                        // Taking via en passant to the right
                        if(movePiece && location.y==3.5+0.5*dir && board.board[location.x+1][location.y].enpassant)
                        {
                        if(board.board[location.x+1][location.y+dir].side!=side && board.board[location.x+1][location.y+dir].what_piece!=blank)
                            board.moves.push_back(convert(location, toCoord(location.x+1, location.y+dir)));

                        // Taking via en passant to the right
                        if(location.y==3.5+0.5*dir && board.enpassant.x == location.x+1 && board.enpassant.y == location.y)
                            board.moves.push_back(convert(location, toCoord(location.x+1, location.y+dir)));
                            */
        }

        // Take to the left
        if(location.x>0)
        {
            //control.push_back(toCoord(location.x-1, location.y+dir));
            if(board.board[location.x-1][location.y+dir].side!=side)
            {
                if(!movePiece && !board.check[!side] && board.board[location.x-1][location.y+dir].what_piece == king)
                    board.check[!side] = true;
                else if(board.board[location.x-1][location.y+dir].what_piece!=blank)
                {
                    board.moves.push_back(convert(location, toCoord(location.x-1, location.y+dir)));
                    if(!board.check[!side] && board.board[location.x-1][location.y+dir].what_piece == king)
                        board.check[!side] = true;
                }
                //attack_option.which_piece.push_back(board.board[location.x - 1][location.y + dir].what_piece);
            }
            /*

                        // Taking via en passant to the left
                        if(movePiece && location.y==3.5+0.5*dir && board.board[location.x-1][location.y].enpassant)
                        {
                            board.moves.push_back(convert(location, toCoord(location.x-1, location.y+dir)));

                        if(location.y==3.5+0.5*dir && board.enpassant.x == location.x-1 && board.enpassant.y == location.y)

                            board.moves.push_back(convert(location, toCoord(location.x-1, location.y+dir)));*/
        }

        break;

    default:
        return;
    }
    return;
}

Board::Board()
{
    check[0]=false;
    check[1]=false;
    //moves.reserve(150);
}

void convert(coord position)
{
    // Convert x and y (from 0 to 7) to chess notation
    cout<<(char)(position.x + 97);

    cout<<position.y + 1;
}

coord convert(string s)
{
    // Value to return
    coord c;

    // Convert x to integer
    switch(s[0])
    {
    case 'a':
        c.x=0;
        break;
    case 'b':
        c.x=1;
        break;
    case 'c':
        c.x=2;
        break;
    case 'd':
        c.x=3;
        break;
    case 'e':
        c.x=4;
        break;
    case 'f':
        c.x=5;
        break;
    case 'g':
        c.x=6;
        break;
    case 'h':
        c.x=7;
        break;
    default:
        c.x=-1;
        break;
    }

    // Convert y to integer
    switch(s[1])
    {
    case '1':
        c.y=0;
        break;
    case '2':
        c.y=1;
        break;
    case '3':
        c.y=2;
        break;
    case '4':
        c.y=3;
        break;
    case '5':
        c.y=4;
        break;
    case '6':
        c.y=5;
        break;
    case '7':
        c.y=6;
        break;
    case '8':
        c.y=7;
        break;
    default:
        c.y=-1;
        break;
    }

    return c;
}

move_store convert(coord start, coord finish)
{
    move_store m;
    m.start_loc = start;
    m.end_loc = finish;
    return m;
}

void Piece::testing()
{
    /*
       // Output information
       cout<<"Source: ";
       convert(location);
       cout << endl;
       cout<<"Piece:"<<what_piece<<endl;
       cout<<"Colour:"<<side<<endl;

       // Output attacking squares
       cout<<"Attacking:";
       for(int i = 0; i < int(attack_option.attack_coord.size()); i++)
       {
           convert(location);
           cout<<"x";
           convert(attack_option.attack_coord[i]);
           cout<<" ";
       }
       cout<<endl;

       // Output movement
       cout<<"Movement:";
       for(int i = 0; i < int(movement.size()); i++)
       {
           convert(movement[i]);
           cout<<" ";
       }
       cout<<endl;*/
}

void Board::testing(int x, int y)
{
    board[x][y].testing();
}

void Board::reset()
{
#define start 1
#if start == 1

    for(int i = 0; i < 2; i++)
    {
        kingCastle[i] = true;
        rookCastle[i] = true;
        rookCastle2[i] = true;
        //castledKing[i] = false;
    }
    for (int i=0; i<8; i++)
    {
        // Set up white pawns
        Piece whitePawn(toCoord(i, 1), pawn, white);
        board[i][1]=whitePawn;

        // Set up black pawns
        Piece blackPawn(toCoord(i, 6), pawn, black);
        board[i][6]=blackPawn;
    }
    // Create white rooks
    Piece whiteRook(toCoord(0, 0), rook, white);
    Piece whiteRook2(toCoord(7, 0), rook, white);

    // Place white rooks on board
    board[0][0]=whiteRook;
    board[7][0]=whiteRook2;

    // Create black rooks
    Piece blackRook(toCoord(0, 7), rook, black);
    Piece blackRook2(toCoord(7, 7), rook, black);

    // Place black rooks on board
    board[0][7]=blackRook;
    board[7][7]=blackRook2;

    // Create white knights
    Piece whiteKnight(toCoord(1, 0), knight, white);
    Piece whiteKnight2(toCoord(6, 0), knight, white);

    // Place white knights on board
    board[1][0]=whiteKnight;
    board[6][0]=whiteKnight2;

    // Create black knights
    Piece blackKnight(toCoord(1, 7), knight, black);
    Piece blackKnight2(toCoord(6, 7), knight, black);

    // Place black knights
    board[1][7]=blackKnight;
    board[6][7]=blackKnight2;

    // Create white bishops
    Piece whiteBishop(toCoord(2, 0), bishop, white);
    Piece whiteBishop2(toCoord(5, 0), bishop, white);

    // Place white bishops
    board[2][0]=whiteBishop;
    board[5][0]=whiteBishop2;

    // Create black bishops
    Piece blackBishop(toCoord(2, 7), bishop, black);
    Piece blackBishop2(toCoord(5, 7), bishop, black);

    // Place black bishops
    board[2][7]=blackBishop;
    board[5][7]=blackBishop2;

    // Create kings
    Piece whiteKing(toCoord(4, 0), king, white);
    Piece blackKing(toCoord(4, 7), king, black);

    // Place kings on board
    board[4][0]=whiteKing;
    board[4][7]=blackKing;

    // Create queens
    Piece whiteQueen(toCoord(3, 0), queen, white);
    Piece blackQueen(toCoord(3, 7), queen, black);

    // Place queens on board
    board[3][0]=whiteQueen;
    board[3][7]=blackQueen;

    Piece emptySquare;
    for (int x=0; x<8; x++)
        for(int y=2; y<6; y++)
            board[x][y]=emptySquare;

    // Set piece counts to normal
    w[king]=1;
    w[queen]=1;
    w[rook]=2;
    w[bishop]=2;
    w[knight]=2;
    w[pawn]=8;

    b[king]=1;
    b[queen]=1;
    b[rook]=2;
    b[bishop]=2;
    b[knight]=2;
    b[pawn]=8;

#endif // start

#if !start

    // Create kings
    Piece whiteKing(toCoord(5, 0), king, white);
    Piece blackKing(toCoord(4, 7), king, black);

    // Place kings on board
    board[5][0]=whiteKing;
    //board[4][7]=blackKing;

    // Create queens
    Piece whiteQueen(toCoord(3, 0), queen, white);
    Piece blackQueen(toCoord(3, 1), queen, black);

    // Place queens on board
    //board[3][0]=whiteQueen;
    board[3][1]=blackQueen;
    // Create white rooks
    Piece blackRook(toCoord(0, 7), rook, black);
    board[0][7] = blackRook;
    /*Piece whiteRook2(toCoord(7, 0), rook, white);

    // Place white rooks on board
    board[0][0]=whiteRook;
    board[7][0]=whiteRook2;*/

    w[king]=1;
    w[queen]=1;
    w[rook]=0;
    w[bishop]=0;
    w[knight]=0;
    w[pawn]=0;

    b[king]=1;
    b[queen]=1;
    b[rook]=1;
    b[bishop]=0;
    b[knight]=0;
    b[pawn]=0;

#endif // !start
}

void Piece::piece_clear()
{
    side = none;
    what_piece = blank;
}

void Piece::operator =(const Piece& startLoc)
{
    location = startLoc.location;
    what_piece = startLoc.what_piece;
    side = startLoc.side;
    dir = startLoc.dir;
}

void Board::operator =(const Board& startLoc)
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
            board[x][y] = startLoc.board[x][y];
    }
    for(int i=0; i<6; i++)
    {
        w[i] = startLoc.w[i];
        b[i] = startLoc.b[i];
    }

    for(int i = 0; i < 2; i ++)
    {
        kingCastle[i] = startLoc.kingCastle[i];
        rookCastle[i] = startLoc.rookCastle[i];
        rookCastle2[i] = startLoc.rookCastle2[i];
        //castledKing[i] = startLoc.castledKing[i];
    }
}

void destroy(node *& n)
{
    for(int i=0; i<(int)n->branches.size(); i++)
        destroy(n->branches[i]);

    delete n;
}
