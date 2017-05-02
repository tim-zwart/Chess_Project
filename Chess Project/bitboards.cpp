// Contains bitboard arguments and related functions

#include "bitboards.h"

bitboard operator +(bitboard first, bitboard second)
{
    // Add boards
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
            first.board[i][j]+=second.board[i][j];
    }
    return first;
}

bitboard operator -(bitboard first, bitboard second)
{
    // Subtract boards
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
            first.board[i][j]-=second.board[i][j];
    }
    return first;
}

coord toCoord(int x, int y)
{
    coord c;
    c.x=x;
    c.y=y;
    return c;
}

Piece::Piece()
{
    what_piece = blank;
    side = none;
    castle=false;
    enpassant=false;
}

Piece::Piece(coord l, chess_piece p, colour s)
{
    location = l;
    what_piece = p;
    side = s;
    if(s == white)
        dir = 1;
    else
        dir = -1;
    if(p == king || p == rook)
        castle=true;
    else
        castle=false;
    enpassant=false;
}

void Piece::moves(pieceBoard board, bitboard attackBoard)
{
    movement.clear();
    attack_option.attack_coord.clear();
    attack_option.which_piece.clear();
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
        // Up
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x][location.y+1].side != side && location.y<7)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x][location.y+1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x, location.y+1));
                attack_option.which_piece.push_back(board.board[location.x][location.y+1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x, location.y+1));
        }

        // Up right
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x+1][location.y+1].side != side && location.x<7 && location.y<7)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x+1][location.y+1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+1, location.y+1));
                attack_option.which_piece.push_back(board.board[location.x+1][location.y+1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x+1, location.y+1));
        }

        // Right
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x+1][location.y].side != side && location.x<7)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x+1][location.y].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+1, location.y));
                attack_option.which_piece.push_back(board.board[location.x+1][location.y].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x+1, location.y));
        }

        // Down Right
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x+1][location.y-1].side != side && location.x<7 && location.y>0)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x+1][location.y-1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+1, location.y-1));
                attack_option.which_piece.push_back(board.board[location.x+1][location.y-1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x+1, location.y-1));
        }

        // Down
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x][location.y-1].side != side && location.y<0)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x][location.y-1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x, location.y-1));
                attack_option.which_piece.push_back(board.board[location.x][location.y-1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x, location.y-1));
        }

        // Down Left
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x-1][location.y-1].side != side && location.x>0 && location.y>0)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x-1][location.y-1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-1, location.y-1));
                attack_option.which_piece.push_back(board.board[location.x-1][location.y-1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x-1, location.y-1));
        }

        // Left
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x-1][location.y].side != side && location.x>0)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x-1][location.y].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-1, location.y));
                attack_option.which_piece.push_back(board.board[location.x-1][location.y].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x-1, location.y));
        }

        // Up Left
        // Ensure that the square is not occupied by a piece of the same colour
        if(board.board[location.x-1][location.y+1].side != side && location.x>0 && location.y<7)
        {
            // If the square is not empty, note it down as an attack
            if(board.board[location.x-1][location.y+1].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-1, location.y+1));
                attack_option.which_piece.push_back(board.board[location.x-1][location.y+1].what_piece);
            }
            // If the square is empty, note it down as a movement
            else
                movement.push_back(toCoord(location.x-1, location.y+1));
        }

        // Castling
        if(castle)
        {
            int y = 3.5-3.5*dir;

            // Castle Kingside
            // Make sure that the squares are not occupied and castling is allowed
            if(board.board[7][y].castle && board.board[6][y].side == none && board.board[5][y].side == none)
            {
                // Make sure that the king is not castling out of or through check
                if(attackBoard.board[4][y]==0 && attackBoard.board[5][y]==0)
                    movement.push_back(toCoord(6, y));
            }


            // Castle Queenside
            if(board.board[0][y].castle && board.board[1][y].side == none && board.board[2][y].side == none && board.board[3][y].side == none)
            {
                // Make sure that the king is not castling out of or through check
                if(attackBoard.board[4][y]==0 && attackBoard.board[3][y]==0 && attackBoard.board[2][y]==0)
                    movement.push_back(toCoord(2, y));
            }
        }
        break;

    case queen:
        // Move as if the queen was a bishop
        what_piece=bishop;
        this->moves(board, attackBoard);

        // Move as if the queen was a rook
        what_piece=rook;
        this->moves(board, attackBoard);

        // Change piece back to a queen
        what_piece=queen;

        break;

    case bishop:
        for (int i=1; i<8; i++)
        {
            // Top Right
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tr && (location.x+i>7 || location.y+i>7 || board.board[location.x+i][location.y+i].side==side))
                tr=false;
            else if(tr && board.board[location.x+i][location.y+i].side != side && board.board[location.x+i][location.y+i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y+i].what_piece);
                tr=false;
            }
            else if(tr)
                movement.push_back(toCoord(location.x+i, location.y+i));

            // Top Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(tl && (location.x-i < 0 || location.y+i > 7 || board.board[location.x-i][location.y+i].side == side))
                tl=false;
            else if(tl && board.board[location.x-i][location.y+i].side != side && board.board[location.x-i][location.y+i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y+i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y+i].what_piece);
                tl=false;
            }
            else if(tl)
                movement.push_back(toCoord(location.x-i, location.y+i));

            // Bottom Right
            // If the position is off ofconvert(movement[i]); the board or a piece of the same colour is in the way, you can't move there
            if(br && (location.x+i>7 || location.y-i<0 || board.board[location.x+i][location.y-i].side==side))
                br=false;
            else if(br && board.board[location.x+i][location.y-i].side != side && board.board[location.x+i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x+i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x+i][location.y-i].what_piece);
                br=false;
            }
            else if(br)
                movement.push_back(toCoord(location.x+i, location.y-i));

            // Bottom Left
            // If the position is off of the board or a piece of the same colour is in the way, you can't move there
            if(bl && (location.x-i<0 || location.y-i<0 || board.board[location.x-i][location.y-i].side==side))
                bl=false;
            else if(bl && board.board[location.x-i][location.y-i].side != side && board.board[location.x-i][location.y-i].side != none)
            {
                attack_option.attack_coord.push_back(toCoord(location.x-i, location.y-i));
                attack_option.which_piece.push_back(board.board[location.x-i][location.y-i].what_piece);
                bl=false;
            }
            else if(bl)
                movement.push_back(toCoord(location.x-i, location.y-i));
            if(!tr && !tl && !br && !bl)
                break;
        }
        break;

    case knight:

        // Knight Movement for tr, tl, dr, dl
        for(int i = -2; i <= 2; i += 4)
        {
            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i > 0 && location.y + 1 < 8 && location.y + 1> 0 &&
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

            // Checks if the location is within the board and doesn't contain a piece from their side
            if(location.x + i < 8 && location.x + i > 0 && location.y - 1 < 8 && location.y - 1 > 0 &&
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
            if(location.x + 1 < 8 && location.x + 1 > 0 && location.y + i < 8 && location.y + i > 0 &&
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
            if(location.x - 1 < 8 && location.x - 1 > 0 && location.y + i < 8 && location.y + i > 0 &&
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

    case rook:
        for(int i=1; i<8; i++)
        {
            // Move Up
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
        if(board.board[location.x+1][location.y+dir].what_piece!=blank)
        {
            if(board.board[location.x+1][location.y+dir].side!=side)
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
        if(board.board[location.x-1][location.y+dir].what_piece!=blank && board.board[location.x-1][location.y+dir].side!=side)
        {
            attack_option.attack_coord.push_back(toCoord(location.x-1, location.y+dir));
            attack_option.which_piece.push_back(board.board[location.x - 1][location.y + dir].what_piece);
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
    cout<<(char)(position.x + 97);

    cout<<position.y + 1;
}

void Piece::testing()
{
    cout<<"Source: ";
    convert(location);
    cout << endl;
    cout<<"Piece:"<<what_piece<<endl;
    cout<<"Colour:"<<side<<endl;
    cout<<"Attacking:";
    for(int i = 0; i < int(attack_option.attack_coord.size()); i++)
    {
        convert(location);
        cout<<"x";
        convert(attack_option.attack_coord[i]);
        cout<<" ";
    }
    cout<<endl;
    cout<<"Movement:";

    for(int i = 0; i < int(movement.size()); i++)
    {
        convert(movement[i]);
        cout<<" ";
    }
    cout<<endl;
}

void outputBitboard(bitboard board)
{
    for (int i=7; i>=0; i--)
    {
        for (int j=0; j<8; j++)
            cout << board.board[j][i] << " ";
        cout << endl;
    }
}

// Add up the squares that are being attacked
void calcBoard(bitboard &write, pieceBoard b, colour side)
{
    // Set everything to 0
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            write.board[i][j] = 0;

    // Add all of the things
    for (int x=0; x<8; x++)
        for (int y=0; y<8; y++)
        {
            // If the piece is the right side
            if(b.board[x][y].side == side)
            {

                // Add all of the possible takes to the board
                for (int z=0; z<int(b.board[x][y].attack_option.attack_coord.size()); z++)
                {
                    coord temp = b.board[x][y].attack_option.attack_coord[z];
                    write.board[temp.x][temp.y]++;
                }

                // Add all of the possible movements to the board
                for (int z=0; z<int(b.board[x][y].movement.size()); z++)
                {
                    coord temp = b.board[x][y].movement[z];
                    if(b.board[x][y].movement[z].x==0 && b.board[x][y].movement[z].y==2)
                    {
                        cout<<x<<endl;
                    }
                    write.board[temp.x][temp.y]++;
                }
            }
        }
}

void resetBoard (pieceBoard &b)
{
    for (int i=0; i<8; i++)
    {
        // Set up white pawns
        Piece whitePawn(toCoord(i, 1), pawn, white);
        b.board[i][1]=whitePawn;

        // Set up black pawns
        Piece blackPawn(toCoord(i, 6), pawn, black);
        b.board[i][6]=blackPawn;
    }
    // Create white rooks
    Piece whiteRook(toCoord(0, 0), rook, white);
    Piece whiteRook2(toCoord(7, 0), rook, white);

    // Place white rooks on board
    b.board[0][0]=whiteRook;
    b.board[7][0]=whiteRook2;

    // Create black rooks
    Piece blackRook(toCoord(0, 7), rook, black);
    Piece blackRook2(toCoord(7, 7), rook, black);

    // Place black rooks on board
    b.board[0][7]=blackRook;
    b.board[7][7]=blackRook2;

    // Create white knights
    Piece whiteKnight(toCoord(1, 0), knight, white);
    Piece whiteKnight2(toCoord(6, 0), knight, white);

    // Place white knights on board
    b.board[1][0]=whiteKnight;
    b.board[6][0]=whiteKnight2;

    // Create black knights
    Piece blackKnight(toCoord(1, 7), knight, black);
    Piece blackKnight2(toCoord(6, 7), knight, black);

    // Place black knights
    b.board[1][7]=blackKnight;
    b.board[6][7]=blackKnight2;

    // Create white bishops
    Piece whiteBishop(toCoord(2, 0), bishop, white);
    Piece whiteBishop2(toCoord(5, 0), bishop, white);

    // Place white bishops
    b.board[2][0]=whiteBishop;
    b.board[5][0]=whiteBishop2;

    // Create black bishops
    Piece blackBishop(toCoord(2, 7), bishop, black);
    Piece blackBishop2(toCoord(5, 7), bishop, black);

    // Place black bishops
    b.board[2][7]=blackBishop;
    b.board[5][7]=blackBishop2;

    // Create kings
    Piece whiteKing(toCoord(4, 0), king, white);
    Piece blackKing(toCoord(4, 7), king, black);

    // Place kings on board
    b.board[4][0]=whiteKing;
    b.board[4][7]=blackKing;

    // Create queens
    Piece whiteQueen(toCoord(3, 0), queen, white);
    Piece blackQueen(toCoord(3, 7), queen, black);

    // Place queens on board
    b.board[3][0]=whiteQueen;
    b.board[3][7]=blackQueen;
}
