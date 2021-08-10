#include <cstdlib>
#include <ctime>

#include <iostream>

#include <SDL2/SDL.h>

#include "gamestate.hpp"

extern SDL_Renderer *gRenderer; // Global renderer that handles all the drawing

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

GameState::GameState(Board *b)
{
    board = b;
}

// Stores current block, deletes filled lines and creates a new block.
void GameState::checkState()
{
    board->storePiece(currentPiece);
    board->clearFullLines();
    createNewPiece();
}

void GameState::createNewPiece()
{
    currentPiece.piece_type = nextPiece.piece_type;
    currentPiece.rotation = nextPiece.rotation;
    currentPiece.r = currentPiece.getInitialOffsetR();
    currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = getRandom(0, 3);
}

void GameState::drawState()
{
    drawBoard();
    drawPiece(currentPiece);
    drawHoldPiece(nextPiece);
}

void GameState::handleEvent(Action action)
{
    switch(action)
    {
        case Action::move_down:
        {
            currentPiece.r++;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.r--;
                checkState();
            }
            break;
        }

        case Action::move_left:
        {
            currentPiece.c--;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.c++;
            }
            break;
        }

        case Action::move_right:
        {
            currentPiece.c++;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.c--;
            }
            break;
        }

        case Action::drop:
        {
            while (board->isPositionLegal(currentPiece))
            {
                currentPiece.r++;
            }
            currentPiece.r--;
            checkState();
            break;
        }

        case Action::rotate:
        {
            currentPiece.rotation = (currentPiece.rotation + 1) % 4;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.rotation = (currentPiece.rotation + 3) % 4;
            }
            break;
        }
    }
}

void GameState::movePieceDown()
{
    currentPiece.r++;
    if (!board->isPositionLegal(currentPiece))
    {
        currentPiece.r--;
        checkState();
    }
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

void GameState::drawBoard()
{
    // First draw the playfield frame
    SDL_Rect left_column = {config::width_to_playfield - config::frame_width, config::height_to_playfield,
                            config::frame_width, config::block_size * config::playfield_height};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAA, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &left_column);

    SDL_Rect right_column = {config::width_to_playfield + config::block_size * config::playfield_width, config::height_to_playfield,
                             config::frame_width, config::block_size * config::playfield_height};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAA, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &right_column);

    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (!board->isBlockFree(row, col))
            {
                SDL_Rect r = {config::width_to_playfield + col * config::block_size, config::height_to_playfield + row * config::block_size,
                              config::block_size, config::block_size};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
                SDL_RenderFillRect(gRenderer, &r);
            }
        }
    }
}

void GameState::drawPiece(Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                SDL_Rect r = {config::width_to_playfield + (col + p.c) * config::block_size, config::height_to_playfield + (row + p.r) * config::block_size,
                              config::block_size, config::block_size};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xAA, 0xAA, 0xFF);
                SDL_RenderFillRect(gRenderer, &r);
            }
        }
    }
}

void GameState::drawHoldPiece(Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                SDL_Rect r = {config::next_box_x + col * config::block_size, config::next_box_y + row * config::block_size,
                              config::block_size, config::block_size};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xAA, 0xAA, 0xFF);
                SDL_RenderFillRect(gRenderer, &r);
            }
        }
    }
}

int GameState::getRandom(int lower_limit, int upper_limit)
{
    return rand() % (upper_limit - lower_limit + 1) + lower_limit;
}

void GameState::initializeState()
{
    srand(time(0));
    // Get random first piece
    currentPiece.piece_type = getRandom(0, 6);
    currentPiece.rotation = getRandom(0, 3);
    currentPiece.r = currentPiece.getInitialOffsetR();
    currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

    // Get random next piece
    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = getRandom(0, 3);
    nextPiece.r = config::next_box_y;
    nextPiece.c = config::next_box_x;
}