#include "gamestate.hpp"

#include <iostream> // DEBUG

#include "inputmanager.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "utilities.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

GameState::GameState (InputManager *manager) : State (manager) { }

GameState::~GameState ()
{
    exit();
}

void GameState::initialize ()
{
    currentPhase = GAME_STARTED;
    board = new Board;
    srand(time(0));
    hold_block_first_time = true;
    hold_block_used = false;
    
    // Get random first piece
    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = 0;                 // Pieces must always start flat according to the offical Tetris guidelines
    createNewPiece(); 
    nextPiece.r = config::next_box_y;
    nextPiece.c = config::next_box_x;

    // Load necessary textures
    tetrominoSprites = new Texture ();
    playfieldFrame = new Texture ();
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    tetrominoSprites->loadFromImage("../../assets/tetrominoSprites.png");
    playfieldFrame->loadFromImage("../../assets/playfieldFrame.png");
    #else
    tetrominoSprites->loadFromImage("../assets/tetrominoSprites.png");
    playfieldFrame->loadFromImage("../assets/playfieldFrame.png");
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

void GameState::exit ()
{
    delete board;
    tetrominoSprites->free();
    playfieldFrame->free();

    nextStateID = STATE_POP;
}

void GameState::run ()
{
    SDL_Event event;
    switch (currentPhase)
    {
        case GAME_STARTED:
        {
            int countdown = 3;
            Texture *countdown_text = new Texture ();
            while (countdown > 0)
            {
                Game::getInstance()->mRenderer->clearScreen();
                draw();
                countdown_text->loadFromText(std::to_string(countdown), config::default_text_color);
                Game::getInstance()->mRenderer->renderTexture(countdown_text, config::logical_window_width/2, config::logical_window_height/2);
                Game::getInstance()->mRenderer->updateScreen();
                SDL_Delay(1000);
                countdown--;
            }
            currentPhase = GAME_PLAYING;
            mInputManager->clearEventQueue();
            time_snap1 = SDL_GetTicks();
            break;
        }

        case GAME_PLAYING:
        {
            if (mInputManager->isGameExiting())
            {
                nextStateID = STATE_EXIT;
            }
            else if (!isGameOver())
            {
                while (SDL_PollEvent(&event) != 0)
                {
                    mInputManager->pollAction(event);
                    handleEvent(mInputManager->getAction());
                }
                
                time_snap2 = SDL_GetTicks();
                if (time_snap2 - time_snap1 >= config::wait_time)
                {
                    movePieceDown();
                    time_snap1 = SDL_GetTicks();
                }
                Game::getInstance()->mRenderer->clearScreen();
                draw();
                Game::getInstance()->mRenderer->updateScreen();
            }
            else
            {
                // Here the game has finished
                currentPhase = GAME_FINISHED;
            }
            break;
        }

        case GAME_FINISHED:
        {
            Texture *gameover_text = new Texture ();
            gameover_text->loadFromText("Game Over!", config::default_text_color);
            if (!mInputManager->isGameExiting())
            {
                while (SDL_PollEvent(&event) != 0)
                {
                    mInputManager->pollAction(event);
                }
                    Game::getInstance()->mRenderer->clearScreen();
                    draw();
                    Game::getInstance()->mRenderer->renderTexture(gameover_text, config::logical_window_width/2, config::logical_window_height/2);
                    Game::getInstance()->mRenderer->updateScreen();
            }
            else
            {
                // Here the game has exited
                nextStateID = STATE_EXIT;
            }
            break;
        }
    }
}

void GameState::update ()
{
    
}

void GameState::draw ()
{
    drawBoard();
    drawCurrentPiece(currentPiece);
    if (!board->isGameOver() && config::ghost_piece_enabled) drawGhostPiece(currentPiece);
    if (!hold_block_first_time) drawHoldPiece(holdPiece);
    drawNextPiece(nextPiece);
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

bool GameState::isGameOver ()
{
    return board->isGameOver();
}

void GameState::createNewPiece ()
{
    currentPiece.piece_type = nextPiece.piece_type;
    currentPiece.rotation = nextPiece.rotation;
    currentPiece.r = currentPiece.getInitialOffsetR();
    currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

    for (int i = 0; i < 2; i++)
    { 
        currentPiece.r++;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.r--;
        }
    }
    if (currentPiece.piece_type > 1)
    {
            currentPiece.r++;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.r--;
            }
    }

    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = 0; // Pieces must always start flat according to the offical Tetris guidelines
}

void GameState::checkState ()
{
    board->storePiece(currentPiece);
    board->clearFullLines();
    if (!board->isGameOver())
    {
        createNewPiece();
    }
    hold_block_used = false;
}

void GameState::handleEvent (Action action)
{
    switch(action)
    {
        case Action::back:
        {
            Game::getInstance()->popState();
            break;
        }
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

        case Action::move_up:
        case Action::rotate:
        {
            currentPiece.rotation = (currentPiece.rotation + 1) % 4;
            if (!board->isPositionLegal(currentPiece))
            {
                currentPiece.rotation = (currentPiece.rotation + 3) % 4;
            }
            break;
        }

        case Action::hold:
        {
            if (hold_block_first_time)
            {
                holdPiece = Piece(currentPiece);
                holdPiece.rotation = 0;
                createNewPiece();
                hold_block_first_time = false;
                hold_block_used = true;
            }
            else if (!hold_block_used)
            {
                swap(currentPiece, holdPiece);
                holdPiece.rotation = 0;
                currentPiece.r = currentPiece.getInitialOffsetR();
                currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

                for (int i = 0; i < 2; i++)
                { 
                    currentPiece.r++;
                    if (!board->isPositionLegal(currentPiece))
                    {
                        currentPiece.r--;
                    }
                }
                if (currentPiece.piece_type > 1)
                {
                        currentPiece.r++;
                        if (!board->isPositionLegal(currentPiece))
                        {
                            currentPiece.r--;
                        }
                }
                hold_block_used = true;
            }
            break;
        }
    }
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

void GameState::drawBoard ()
{
    for (int i = 0; i < 2*config::true_playfield_height; i++)
    {
        // Left frame
        playfieldFrame->render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield + i*config::frame_sprite_size,
            &playfieldFrameClips[0]);
        // Right frame
        playfieldFrame->render(config::width_to_playfield + config::block_size * config::playfield_width - (config::frame_sprite_size -
        config::frame_width), config::height_to_playfield + i*config::frame_sprite_size, &playfieldFrameClips[0]);
    }
    // Then the 2 corners
    playfieldFrame->render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield + 
        config::block_size*config::true_playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[2]);
    playfieldFrame->render(config::width_to_playfield + config::block_size * config::playfield_width, config::height_to_playfield + 
        config::block_size*config::true_playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[3]);
    
    for (int i = 0; i < 2*config::playfield_width; i++)
    {
        // And the bottom frame
        playfieldFrame->render(config::width_to_playfield + i*config::frame_sprite_size, config::height_to_playfield +
            config::block_size*config::true_playfield_height, &playfieldFrameClips[1]);
    }

    // Then draw the placed blocks
    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (!board->isBlockFree(row, col))
            {
                tetrominoSprites->render(config::width_to_playfield + col * config::block_size, config::height_to_playfield +
                (row-(config::playfield_height-config::true_playfield_height))*config::block_size, &tetrominoSpriteClips[board->getTetromino(row, col)]);
            }
        }
    }
}

void GameState::drawCurrentPiece (Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites->render(config::width_to_playfield + (col+p.c) * config::block_size, config::height_to_playfield +
                (row+p.r-(config::playfield_height-config::true_playfield_height)) *config::block_size, &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

void GameState::drawNextPiece (Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites->render(config::next_box_x + col*config::block_size, config::next_box_y + row*config::block_size,
                                        &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

void GameState::drawHoldPiece (Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites->render(config::hold_box_x + col*config::block_size, config::hold_box_y + row*config::block_size,
                                        &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

void GameState::drawGhostPiece (Piece p)
{
    ghostPiece = p;
    while (board->isPositionLegal(ghostPiece))
    {
        ghostPiece.r++;
    }
    ghostPiece.r--;

    tetrominoSprites->setAlphaMode(config::transparency_alpha);  // Change transparency to render the ghost piece

    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (ghostPiece.getBlockType(row, col) != 0)
            {
                tetrominoSprites->render(config::width_to_playfield + (col+ghostPiece.c) * config::block_size, config::height_to_playfield +
                (row+ghostPiece.r-(config::playfield_height-config::true_playfield_height))*config::block_size, &tetrominoSpriteClips[ghostPiece.piece_type]);
            }
        }
    }

    tetrominoSprites->setAlphaMode(255); // Don't forget to change it back to normal!
}

int GameState::getRandom (int lower_limit, int upper_limit)
{
    return rand() % (upper_limit - lower_limit + 1) + lower_limit;
}