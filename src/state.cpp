#include "state.hpp"

#include "game.hpp"
#include "inputmanager.hpp"

State::State (InputManager *manager)
{
    mInputManager = manager;
}

void State::popState (Game *game)
{
    game->popState();
}

void State::pushState (Game *game, State *state)
{
    game->pushState(state);
}

void State::changeState (Game *game, State *state)
{
    game->changeState(state);
}