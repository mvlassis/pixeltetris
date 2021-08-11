#include "board.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Board::Board()
{
    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            board_state[row][col] = BlockStatus::block_empty;
        }
    }
}

int Board::getTetromino (int r, int c)
{
    return int(board_state[r][c])-1;
}

// True if a block is unoccupied
bool Board::isBlockFree (int r, int c)
{
    // X is the column, Y is the row
    return (board_state[r][c] == BlockStatus::block_empty) ? true : false;
}

// True if a certain move is possible
bool Board::isPositionLegal (Piece p)
{
    for (int row = p.r; row < p.r+config::matrix_blocks; row++)
    {
        for (int col = p.c; col < p.c+config::matrix_blocks; col++)
        {
            // If outside of playfield limits
            if (col < 0 || col > (config::playfield_width-1) || row > (config::playfield_height-1))
            {
                if (p.getBlockType(row-p.r, col-p.c) != 0)
                {
                    return false;
                }
            }

            // If a block collides with a filled block
            if (row >= 0)
            {
                if (p.getBlockType(row-p.r, col-p.c) != 0 && !isBlockFree(row, col))
                {
                    return false;
                }
            }
        }
    }

    // No collisions found
    return true;
}

// Stores a piece in the board
void Board::storePiece (Piece p)
{
    for (int row = p.r; row < p.r+config::matrix_blocks; row++)
    {
        for (int col = p.c; col < p.c+config::matrix_blocks; col++)
        {
            if (p.getBlockType(row-p.r, col-p.c) != 0)
            {
                board_state[row][col] = static_cast<BlockStatus>(1+p.piece_type);
            }
        }
    }
    pieces.push_back(p);
}

// Clears filled lines
void Board::clearFullLines()
{
    for (int row = 0; row < config::playfield_height; row++)
    {
        bool line_filled = true;
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (isBlockFree(row, col))
            {
                line_filled = false;
            } 
        }
        if (line_filled)
        {
            deleteLine(row);
        }
    }
}

// True if the game has ended; Note: the row index starts from the top
bool Board::isGameOver ()
{
    bool game_over = false;
    for (int col = 0; col < config::playfield_width; col++)
    {
        if (board_state[0][col] != BlockStatus::block_empty)
        {
            game_over = true;
            break;
        }
    }
    return game_over;
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

// Clears a filled row and moves all other blocks properly
void Board::deleteLine (int r)
{
    for (int row = r; row > 0; row--)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            board_state[row][col] = board_state[row-1][col];
        }
    }
}