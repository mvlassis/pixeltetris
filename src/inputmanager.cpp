#include "inputmanager.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

void InputManager::clearEventQueue()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        
    }
}

Action InputManager::getAction()
{
    return action;
}

bool InputManager::isGameExiting()
{
    return quit_game;
}

// Polls from keyboard and gets the corresponding action
void InputManager::pollAction(SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        quit_game = true;
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
    {
        quit_game = true;
    }
    else if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_DOWN:
            {
                action = Action::move_down;
                break;
            }

            case SDLK_LEFT:
            {
                action = Action::move_left;
                break;
            }

            case SDLK_RIGHT:
            {
                action = Action::move_right;
                break;
            }

            case SDLK_SPACE:
            {
                action = Action::drop;
                break;
            }

            case SDLK_UP: case SDLK_x:
            {
                action = Action::rotate;
                break;
            }
        }
    }
    else
    {
        action = Action::stay_idle;
    }
}

void InputManager::setExit()
{
    quit_game = true;
}