#ifndef STATE_HPP
#define STATE_HPP

#include "game.hpp"
#include "inputmanager.hpp"
#include "renderer.hpp"

enum StateID {STATE_NULL, STATE_EXIT, STATE_POP, STATE_PLAY, STATE_MENU, STATE_PAUSE};

class Game;

class State
{
public:
    State(InputManager *manager, Renderer *renderer);
    virtual void initialize () = 0;
    virtual void exit () = 0;

    virtual void run () = 0;
    virtual void update () = 0;
    virtual void draw () = 0;

    void popState (Game *game);
    void pushState (Game *game, State *state);
    void changeState (Game *game, State *state);
    StateID nextStateID;

protected:
    InputManager *mInputManager;
    Renderer *mRenderer;
};

#endif // STATE_HPP