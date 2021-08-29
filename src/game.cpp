#include "game.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "config.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"
#include "state.hpp"

bool Game::initialize()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initialize SDL! SDL_Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        mWindow = SDL_CreateWindow(config::window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        config::logical_window_width, config::logical_window_height, SDL_WINDOW_SHOWN);

        if (mWindow == nullptr)
        {
            std::cerr << "Could not create window! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            if (IMG_Init(IMG_INIT_PNG) == 0 || IMG_Init(IMG_INIT_JPG) == 0)
            {
                std::cerr << "Could not initialize SDL_image! SDL_image error: " << IMG_GetError() << '\n';
                success = false;
            }
            if (TTF_Init() == -1)
            {
                std::cerr << "Could not initialize SDL_ttf! SDL_ttf error: " << TTF_GetError() << '\n';
                success = false;
            }
        }
    }
    mRenderer = new Renderer;
    mRenderer->initialize(mWindow);
    // Now load the main menu screen
    // mMainMenuState = new MenuState(new InputManager, new Renderer);
    pushState(new GameState (new InputManager, mRenderer));
    mStates.back()->initialize();
    std::cerr << "Initialization done\n";
    return success;
}

void Game::exit ()
{
    for (auto i : mStates)
    {
        delete i;
    }
    TTF_CloseFont(mFont);
    mFont = nullptr;

    delete mRenderer;

    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run ()
{
    while (!mStates.empty())
    {
        mStates.back()->run();
        if (mStates.back()->nextStateID != STATE_NULL)
        {
            if (mStates.back()->nextStateID == STATE_EXIT)
            {
                break;
            }
            else switch (mStates.back()->nextStateID)
            {
                case STATE_POP:
                {
                    popState();
                }
                case STATE_PLAY:
                {
                    pushState(new GameState (new InputManager, new Renderer));
                }
            }
        }
    }
    exit();
}

void Game::popState ()
{
    mStates.pop_back();
}

void Game::pushState (State *state)
{
    mStates.push_back(state);
}

void Game::changeState (State *state)
{
    popState();
    pushState(state);
}

bool Game::isGameExiting ()
{
    return mStates.back()->nextStateID == STATE_EXIT;
}