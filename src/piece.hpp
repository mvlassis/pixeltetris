#ifndef PIECES_HPP
#define PIECES_HPP

class Piece
{
    friend class Board;
    friend class GameState;
public:
    Piece (int p_piece_type, int p_rotation); // Initialize a piece with these values
    int getBlockType (int r_offset, int c_offset); // Returns the block type for a certain piece, rotation, and position
    int getInitialOffsetR (); // Returns the initial position offset for the row
    int getInitialOffsetC (); // Returns the initial position offset for the column
private:
    int piece_type; // Type of tetromino
    int rotation; // One of four possible rotations
    int r; // Row index
    int c; // Column index
};



#endif // PIECES_HPP