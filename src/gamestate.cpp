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

GameState::GameState()
{
    board = new Board;
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
    nextPiece.rotation = 0; // Pieces must always start flat according to the offical Tetris guidelines
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

void GameState::initializeState ()
{
    srand(time(0));
    // Get random first piece
    currentPiece.piece_type = getRandom(0, 6);
    currentPiece.rotation = 0;   // Pieces must always start flat according to the offical Tetris guidelines
    currentPiece.r = currentPiece.getInitialOffsetR();
    currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

    // Get random next piece
    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = 0;     // Pieces must always start flat according to the offical Tetris guidelines
    nextPiece.r = config::next_box_y;
    nextPiece.c = config::next_box_x;

    // Load necessary textures
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    tetrominoSprites.loadFromImage("../../assets/tetrominoSprites.png");
    playfieldFrame.loadFromImage("../../assets/playfieldFrame.png");
    #else
    tetrominoSprites.loadFromImage("../assets/tetrominoSprites.png");
    playfieldFrame.loadFromImage("../assets/playfieldFrame.png");
    #endif

    // Create the right clips sprites
    for (int i = 0; i < 7; i++)
    {
        tetrominoSpriteClips[i].x = 16*i;
        tetrominoSpriteClips[i].y = 0;
        tetrominoSpriteClips[i].w = 16;
        tetrominoSpriteClips[i].h = 16;
    }
    for (int i = 0; i < 4; i++)
    {
        playfieldFrameClips[i].x = config::frame_sprite_size*i;
        playfieldFrameClips[i].y = 0;
        playfieldFrameClips[i].w = config::frame_sprite_size;
        playfieldFrameClips[i].h = config::frame_sprite_size;
    }
}

bool GameState::isGameOver ()
{
    return board->isGameOver();
}

void GameState::movePieceDown ()
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
    // SDL_Rect left_column = {config::width_to_playfield - config::frame_width, config::height_to_playfield,
    //                         config::frame_width, config::block_size * config::playfield_height};
    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAA, 0xFF, 0xFF);
    // SDL_RenderFillRect(gRenderer, &left_column);

    // SDL_Rect right_column = {config::width_to_playfield + config::block_size * config::playfield_width, config::height_to_playfield,
    //                          config::frame_width, config::block_size * config::playfield_height};
    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAA, 0xFF, 0xFF);
    // SDL_RenderFillRect(gRenderer, &right_column);

    for (int i = 0; i < 2*config::playfield_height; i++)
    {
        // Left frame
        playfieldFrame.render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield + i*config::frame_sprite_size,
            &playfieldFrameClips[0]);
        // Right frame
        playfieldFrame.render(config::width_to_playfield + config::block_size * config::playfield_width - (config::frame_sprite_size -
        config::frame_width), config::height_to_playfield + i*config::frame_sprite_size, &playfieldFrameClips[0]);
    }
    // Then the 2 corners
    playfieldFrame.render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield + 
        config::block_size*config::playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[2]);
    playfieldFrame.render(config::width_to_playfield + config::block_size * config::playfield_width, config::height_to_playfield + 
        config::block_size*config::playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[3]);
    
    for (int i = 0; i < 2*config::playfield_width; i++)
    {
        // And the bottom frame
        playfieldFrame.render(config::width_to_playfield + i*config::frame_sprite_size, config::height_to_playfield +
            config::block_size*config::playfield_height, &playfieldFrameClips[1]);
    }

    // Then draw the placed blocks
    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (!board->isBlockFree(row, col))
            {
                tetrominoSprites.render(config::width_to_playfield + col * config::block_size, config::height_to_playfield + row *config::block_size,
                                        &tetrominoSpriteClips[board->getTetromino(row, col)]);
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
                tetrominoSprites.render(config::width_to_playfield + (col+p.c) * config::block_size, config::height_to_playfield + (row+p.r) *config::block_size,
                                        &tetrominoSpriteClips[p.piece_type]);
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
                tetrominoSprites.render(config::next_box_x + col*config::block_size, config::next_box_y + row*config::block_size,
                                        &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

int GameState::getRandom(int lower_limit, int upper_limit)
{
    return rand() % (upper_limit - lower_limit + 1) + lower_limit;
}