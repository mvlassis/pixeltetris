#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "inputmanager.hpp"
#include "renderer.hpp"
#include "state.hpp"

class State;

class Game
{
public:
    bool initialize ();
    void exit ();
    void run ();
    
    void popState ();
    void pushState (State *s);
    void changeState (State *s);

    bool isGameExiting();
private:
    SDL_Window *mWindow;
    Renderer *mRenderer;
    InputManager *mManager;
    std::vector<State*> mStates;

    State *mPlayState;
    State *mMainMenuState;

    TTF_Font *mFont;
};

#endif // GAME_HPP