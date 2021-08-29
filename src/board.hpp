#ifndef BOARD_HPP
#define BOARD_HPP

#include "config.hpp"
#include "piece.hpp"

#include <vector>

enum BlockStatus : int {block_empty, i_block, o_block, t_block, s_block, z_block, j_block, l_block};

class Board
{
public:
    Board ();
    int getTetromino (int r, int c);    // Returns type of tetromino
    bool isBlockFree (int r, int c);    // True if a block is unoccupied
    bool isPositionLegal (Piece p);     // True if a certain move is possible
    void storePiece (Piece p);          // Stores a piece in the board
    void clearFullLines ();             // Clears filled lines
    bool isGameOver ();                 // True if the game has ended; Note: the row index starts from the top

private:
    BlockStatus board_state [config::playfield_height][config::playfield_width]; // +2 is for spawning above the playfield
    std::vector<Piece> pieces;

    void deleteLine (int y);            // Clears a filled row and moves all other blocks properly
};

#endif // BOARD_HPP