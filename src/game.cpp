#include "game.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "button.hpp"
#include "config.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"
#include "state.hpp"

Game *Game::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Game;
    }
    return instance;
}

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
    mManager = new InputManager;

    // Now load the main menu screen
    mMainMenuState = new MenuState(mManager);
    mSettingsState = new MenuState(mManager);
    mMainMenuState->addButton(new Button ("../assets/button-play.png", &Game::pushNewGame, (config::logical_window_width-80)/2, 100));
    mMainMenuState->addButton(new Button ("../assets/button-exit.png", &Game::pushExit, (config::logical_window_width-80)/2, 160));
    // mMainMenuState->addButton();
    pushState(mMainMenuState);
    // pushState(mPlayState);
    mStates.back()->initialize();
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
    if (!mStates.empty())
    {
        mStates.back()->run();
        if (!mStates.empty() && mStates.back()->nextStateID != STATE_NULL)
        {
            switch (mStates.back()->nextStateID)
            {
                case STATE_POP:
                {
                    popState();
                    break;
                }
                case STATE_PLAY:
                {
                    pushState(new GameState (new InputManager));
                    break;
                }
            }
        }
    }
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

void Game::pushNewGame ()
{
    delete Game::getInstance()->mPlayState;
    Game::getInstance()->mPlayState = new GameState(Game::getInstance()->mManager);
    Game::getInstance()->mPlayState->initialize();
    Game::getInstance()->pushState(Game::getInstance()->mPlayState);
}

void Game::pushSettings ()
{
    // this
}

void Game::pushExit ()
{
    Game::getInstance()->popState();
}

bool Game::isGameExiting ()
{
    if (mStates.empty())
    {
        return true;
    }
    else
    {
        return mStates.back()->nextStateID == STATE_EXIT;
    }
}

Game *Game::instance = 0;

Game::Game () {}