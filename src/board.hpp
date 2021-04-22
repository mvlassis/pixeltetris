#ifndef BOARD_HPP
#define BOARD_HPP

#include "config.hpp"

#include <vector>

#include "piece.hpp"

enum class BlockStatus {block_empty, block_filled};

class Board
{
public:
    Board ();
    bool isBlockFree (int r, int c); // True if a block is unoccupied
    bool isPositionLegal (Piece p);  // True if a certain move is possible
    void storePiece (Piece p);       // Stores a piece in the board
    void clearFullLines ();          // Clears filled lines
    bool isGameOver ();              // True if the game has ended; Note: the row index starts from the top

private:
    BlockStatus board_state [config::playfield_height][config::playfield_width];
    std::vector<Piece> pieces;

    void deleteLine (int y);         // Clears a filled row and moves all other blocks properly
};

#endif // BOARD_HPP