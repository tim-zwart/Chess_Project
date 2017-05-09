// Contains bitboard arguments and related functions

#include "bitboards.h"

<<<<<<< HEAD
// Outputs the entire board with pieces represented with upper and lower case letter.
=======
// Output Board class
>>>>>>> refs/remotes/origin/master
ostream & operator<<(ostream & stream, Board b)
{
    // Go throught the entire board
    for (int i=7; i>=0; i--)
    {
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
    return stream;
}

// Changes a given x and y integer to a coord struct.
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
    castle=false;
    enpassant=false;
}

<<<<<<< HEAD
// Piece constructor with given values
=======
// Piece constructor
>>>>>>> refs/remotes/origin/master
Piece::Piece(coord l, chess_piece p, colour s)
{
    // Set everything to the input
    location = l;
    what_piece = p;
    side = s;

    // Set direction depending on side
    if(s == white)
        dir = 1;
    else
        dir = -1;

    // Chec whether pieces can castle
    if((p == king || p == rook) && l.y==3.5-3.5*dir)
        castle=true;
    else
        castle=false;
    enpassant=false;
}

//
void Piece::moves(Board &board)
{
    // Get adress to read from depending on colour
    int *b[8];
    if(side==white)
    {
        for (int i=0; i<8; i++)
            b[i]=(int*)board.whiteControl[i];
    }
    else if(side==black)
        for (int i=0; i<8; i++)
            b[i]=(int*)board.blackControl[i];

    // Reset vectors
    movement.clear();
    control.clear();
    attack_option.attack_coord.clear();
    attack_option.which_piece.clear();

    // The depth for rooks and bishops to move
    int distance = 7;

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
        // Go throuch as if the king was a bishop and a rook but only going one move deep
        distance = 2;

    case queen:
    // Go through as if the queen was a bishop and a rook

    case bishop:
        for (int i=1; i<distance; i++)
        {
            // Top Right
            if(tr && location.x+i<8 && location.y+i<8)
                control.push_back(toCoord(location.x+i, location.y+i));
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tr && (location.x+i>7 || location.y+i>7 || board.board[location.x+i][location.y+i].side==side))
                tr=false;
            else if(tr && board.board[location.x+i][location.y+i].side != side && board.board[location.x+i][location.y+i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                control.push_back(toCoord(location.x+i, location.y+i));
                tr=false;
            }
            else if(tr)
            {
                movement.push_back(toCoord(location.x+i, location.y+i));
                control.push_back(toCoord(location.x+i, location.y+i));
            }

            // Top Left
            if(tl && location.x-i>=0 && location.y+i<8)
                control.push_back(toCoord(location.x-i, location.y+i));
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tl && (location.x-i < 0 || location.y+i > 7 || board.board[location.x-i][location.y+i].side == side))
                tl=false;
            else if(tl && board.board[location.x-i][location.y+i].side != side && board.board[location.x-i][location.y+i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y+i].what_piece);
                control.push_back(toCoord(location.x-i, location.y+i));
                tl=false;
            }
            else if(tl)
            {
                movement.push_back(toCoord(location.x-i, location.y+i));
                control.push_back(toCoord(location.x-i, location.y+i));
            }

            // Bottom Right
            if(br && location.x+i<8 && location.y-i>0)
                control.push_back(toCoord(location.x+i, location.y-i));
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                br=false;
            else if(br && board.board[location.x+i][location.y-i].side != side && board.board[location.x+i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y-i].what_piece);
                control.push_back(toCoord(location.x+i, location.y-i));
                br=false;
            }
            else if(br)
            {
                movement.push_back(toCoord(location.x+i, location.y-i));
                control.push_back(toCoord(location.x+i, location.y-i));
            }

            // Bottom Left
            if(bl && location.x-i>=0 && location.y-i>=0)
                control.push_back(toCoord(location.x-i, location.y-i));
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(bl && (location.x-i<0 || location.y-i<0 || board.board[location.x-i][location.y-i].side==side))
                bl=false;
            else if(bl && board.board[location.x-i][location.y-i].side != side && board.board[location.x-i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y-i].what_piece);
                control.push_back(toCoord(location.x-i, location.y-i));
                bl=false;
            }
            else if(bl)
            {
                movement.push_back(toCoord(location.x-i, location.y-i));
                control.push_back(toCoord(location.x-i, location.y-i));
            }
            if(!tr && !tl && !br && !bl)
                break;
        }
<<<<<<< HEAD
        break;

    case knight:

        // Knight Movement for tr, tl, dr, dl
        for(int i = -2; i <= 2; i += 4)
        {
            // Knight movement for two squares to the left and right, and one square up
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y + 1 < 8 &&
                    board.board[location.x + i][location.y + 1].side != side)
            {
                //Checks if the location isn't blank
                if(board.board[location.x + i][location.y + 1].what_piece != blank)
                {
                    attack_option.attack_coord.push_back(toCoord(location.x + i, location.y + 1));
                    attack_option.which_piece.push_back(board.board[location.x + i][location.y + 1].what_piece);
                }
                // If there isn't a piece adds it to movement
                else
                    movement.push_back(toCoord(location.x + i, location.y + 1));
            }

            // Knight movement for two squares to the left and right, and one square down
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y - 1 >= 0 &&
                    board.board[location.x + i][location.y - 1].side != side)
            {
                //Checks if the location isn't blank
                if(board.board[location.x + i][location.y - 1].what_piece != blank)
                {
                    attack_option.attack_coord.push_back(toCoord(location.x + i, location.y - 1));
                    attack_option.which_piece.push_back(board.board[location.x + i][location.y - 1].what_piece);
                }
                // If there isn't a piece adds it to movement
                else
                    movement.push_back(toCoord(location.x + i, location.y - 1));
            }
            // Knight movement for two squares up and down, and one square to the right
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + 1 < 8 && location.y + i < 8 && location.y + i >= 0 &&
                    board.board[location.x + 1][location.y + i].side != side)
            {
                //Checks if the location isn't blank
                if(board.board[location.x + 1][location.y + i].what_piece != blank)
                {
                    attack_option.attack_coord.push_back(toCoord(location.x + 1, location.y + i));
                    attack_option.which_piece.push_back(board.board[location.x + 1][location.y + i].what_piece);
                }
                // If there isn't a piece adds it to movement
                else
                    movement.push_back(toCoord(location.x + 1, location.y + i));
            }
            // Knight movement for two squares up and down, and one square to the left
            // Checks if the location is within the board and doesn't contain a piece nfrom their side
            if(location.x - 1 >= 0 && location.y + i < 8 && location.y + i >= 0 &&
                    board.board[location.x - 1][location.y + i].side != side)
            {
                //Checks if the location isn't blank
                if(board.board[location.x - 1][location.y + i].what_piece != blank)
                {
                    attack_option.attack_coord.push_back(toCoord(location.x - 1, location.y + i));
                    attack_option.which_piece.push_back(board.board[location.x - 1][location.y + i].what_piece);
                }
                // If there isn't a piece adds it to movement
                else
                    movement.push_back(toCoord(location.x - 1, location.y + i));
            }
        }
        break;
=======
        if(what_piece==bishop)
            break;
>>>>>>> refs/remotes/origin/master

    case rook:
        for(int i=1; i<distance; i++)
        {
            // Move Up
            if(u && location.y+i<8)
                control.push_back(toCoord(location.x, location.y+i));
            if(u && (location.y+i>7 || board.board[location.x][location.y+i].side == side))
                u=false;
            else if(u && board.board[location.x][location.y+i].what_piece != blank && board.board[location.x][location.y+i].side != side)
            {
                attack_option.attack_coord.push_back(toCoord(location.x, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x][location.y+i].what_piece);
                u=false;
            }
            else if (u)
                movement.push_back(toCoord(location.x, location.y+i));

            // Move Down
            if(d && location.y-i>=0)
                control.push_back(toCoord(location.x, location.y-i));
            if(d && (location.y-i<0 || board.board[location.x][location.y-i].side == side))
                d=false;
            else if(d && board.board[location.x][location.y-i].what_piece != blank && board.board[location.x][location.y-i].side != side)
            {
                attack_option.attack_coord.push_back(toCoord(location.x, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x][location.y-i].what_piece);
                d=false;
            }
            else if (d)
                movement.push_back(toCoord(location.x, location.y-i));

            // Move Right
            if(r && location.x+i<8)
                control.push_back(toCoord(location.x+i, location.y));
            if(r && (location.x+i>7 || board.board[location.x+i][location.y].side == side))
                r=false;
            else if(r && board.board[location.x+i][location.y].what_piece != blank && board.board[location.x+i][location.y].side != side)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y].what_piece);
                r=false;
            }
            else if (r)
                movement.push_back(toCoord(location.x+i, location.y));

            // Move Left
            if(l && location.x-i>=0)
                control.push_back(toCoord(location.x-i, location.y));
            if(l && (location.x-i<0 || board.board[location.x-i][location.y].side == side))
                l=false;
            else if(l && board.board[location.x-i][location.y].what_piece != blank && board.board[location.x-i][location.y].side != side)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y].what_piece);

                l=false;
            }
            else if (l)
                movement.push_back(toCoord(location.x-i, location.y));
        }
        break;

    case knight:

        // Knight Movement for tr, tl, dr, dl
        for(int i = -2; i <= 2; i += 4)
        {
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y + 1 < 8)
            {
                control.push_back(toCoord(location.x + i, location.y + 1));
                if(board.board[location.x + i][location.y + 1].side != side)
                {
                    //Checks if the location isn't blank
                    if(board.board[location.x + i][location.y + 1].what_piece != blank)
                    {
                        attack_option.attack_coord.push_back(toCoord(location.x + i, location.y + 1));
                        attack_option.which_piece.push_back(board.board[location.x + i][location.y + 1].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        movement.push_back(toCoord(location.x + i, location.y + 1));
                }
            }

            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i >= 0 && location.y - 1 >= 0)
            {
                control.push_back(toCoord(location.x + i, location.y - 1));
                if(board.board[location.x + i][location.y - 1].side != side)
                {
                    //Checks if the location isn't blank
                    if(board.board[location.x + i][location.y - 1].what_piece != blank)
                    {
                        attack_option.attack_coord.push_back(toCoord(location.x + i, location.y - 1));
                        attack_option.which_piece.push_back(board.board[location.x + i][location.y - 1].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        movement.push_back(toCoord(location.x + i, location.y - 1));
                }
            }
            if(location.x + 1 < 8 && location.y + i < 8 && location.y + i >= 0)
            {
                control.push_back(toCoord(location.x + 1, location.y + i));
                if(board.board[location.x + 1][location.y + i].side != side)
                {
                    //Checks if the location isn't blank
                    if(board.board[location.x + 1][location.y + i].what_piece != blank)
                    {
                        attack_option.attack_coord.push_back(toCoord(location.x + 1, location.y + i));
                        attack_option.which_piece.push_back(board.board[location.x + 1][location.y + i].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        movement.push_back(toCoord(location.x + 1, location.y + i));
                }
            }
            if(location.x - 1 >= 0 && location.y + i < 8 && location.y + i >= 0)
            {
                control.push_back(toCoord(location.x - 1, location.y + i));
                if(board.board[location.x - 1][location.y + i].side != side)
                {
                    //Checks if the location isn't blank
                    if(board.board[location.x - 1][location.y + i].what_piece != blank)
                    {
                        attack_option.attack_coord.push_back(toCoord(location.x - 1, location.y + i));
                        attack_option.which_piece.push_back(board.board[location.x - 1][location.y + i].what_piece);
                    }
                    // If there isn't a piece adds it to movement
                    else
                        movement.push_back(toCoord(location.x - 1, location.y + i));
                }
            }
        }
        break;

    case pawn:
        // Moves for pawns

        // Moving forward
        if(board.board[location.x][location.y+dir].what_piece==blank)
        {
            movement.push_back(toCoord(location.x, location.y+dir));

            // Moving forward 2 from the seventh rank
            if(location.y==(3.5-2.5*dir) && board.board[location.x][location.y+2*dir].what_piece==blank)
                movement.push_back(toCoord(location.x, location.y+2*dir));
        }

        // Take to the right
        if(location.x<7)
        {
            control.push_back(toCoord(location.x+1, location.y+dir));
            if(board.board[location.x+1][location.y+dir].side!=side && board.board[location.x+1][location.y+dir].what_piece!=blank)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+1, location.y+dir));
                attack_option.which_piece.push_back(board.board[location.x + 1][location.y+dir].what_piece);
            }
        }
        // Taking via en passant to the right
        else if(location.y==3.5+0.5*dir && board.board[location.x+1][location.y].enpassant)
        {
            attack_option.attack_coord.push_back(toCoord(location.x+1, location.y+dir));
            attack_option.which_piece.push_back(board.board[location.x + 1][location.y].what_piece);
        }
        // Take to the left
        if(location.x>0)
        {
            control.push_back(toCoord(location.x-1, location.y+dir));
            if(board.board[location.x-1][location.y+dir].what_piece!=blank && board.board[location.x-1][location.y+dir].side!=side)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-1, location.y+dir));
                attack_option.which_piece.push_back(board.board[location.x - 1][location.y + dir].what_piece);
            }
        }

        // Taking via en passant to the left
        else if(location.y==3.5+0.5*dir && board.board[location.x-1][location.y].enpassant)
        {
            attack_option.attack_coord.push_back(toCoord(location.x-1, location.y+dir));
            attack_option.which_piece.push_back(board.board[location.x - 1][location.y].what_piece);
        }

        break;

    default:
        return;
    }

    return;
}

void Piece::convert(coord position)
{
    // Convert x and y (from 0 to 7) to chess notation
    cout<<(char)(position.x + 97);

    cout<<position.y + 1;
}

void Piece::testing()
{
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
    cout<<endl;
}

void Board::outputBoard(colour side)
{
    // Find location to read from
    int *b[8];
    if(side==white)
    {
        for (int i=0; i<8; i++)
            b[i]=(int*)this->whiteControl[i];
    }
    else if(side==black)
        for (int i=0; i<8; i++)
            b[i]=(int*)this->blackControl[i];

    // Go through board and output
    for (int i=7; i>=0; i--)
    {
        for (int j=0; j<8; j++)
            cout << b[j][i] << " ";
        cout << endl;
    }
}

// Add up the squares that are being attacked
void Board::calcBoard(colour side)
{
    // Find location to write to
    int *b[8];
    if(side==white)
    {
        for (int i=0; i<8; i++)
            b[i]=(int*)this->whiteControl[i];
    }
    else if(side==black)
        for (int i=0; i<8; i++)
            b[i]=(int*)this->blackControl[i];

    // Set everything to 0
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            b[i][j] = 0;

    // Add all of the attacks and movements
    for (int x=0; x<8; x++)
        for (int y=0; y<8; y++)
        {
            // If the piece is the right side
            if(board[x][y].side == side)
            {
                // Add all of the possible movements to the board
                for (int z=0; z<int(board[x][y].control.size()); z++)
                {
                    coord temp = board[x][y].control[z];
                    b[temp.x][temp.y]++;

                    if(temp.x==0 && temp.y==7)
                    {
                        cout << board[x][y].what_piece << endl << "x:" << x << "  y:" << y << "\n\n";
                    }


                }
            }
        }
}

void Board::reset()
{
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
}

void Piece::piece_clear()
{
    movement.clear();
    attack_option.attack_coord.clear();
    attack_option.which_piece.clear();
    side = none;
    what_piece = blank;
}
