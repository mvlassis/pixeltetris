#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "inputmanager.hpp"
#include "renderer.hpp"
#include "state.hpp"

class State;
class GameState;
class MenuState;
class OptionsState;
class PausedState;

// Utilizes the "Singleton pattern" to ensure there can only be one game
class Game
{
public:
    friend class OptionsState;          // Options can change the window size            
    static Game* getInstance();

    bool initialize ();
    void exit ();
    void run ();
    
    void popState ();
    void pushState (State *s);
    void changeState (State *s);

    static void pushOptions();
    static void pushNewGame();
    static void pushPaused();
    static void goBack();
    static void goDoubleBack();

    bool isGameExiting();

    Renderer *mRenderer;                // The renderer used for all things rendering
    
private:
    static Game *mInstance;
    Game();
    SDL_Window *mWindow;
    InputManager *mManager;
    std::vector<State*> mStates;

    GameState *mPlayState;
    MenuState *mMainMenuState;
    OptionsState *mOptionsState;
    PausedState *mPausedState;
};

#endif // GAME_HPP