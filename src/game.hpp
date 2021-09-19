#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "inputmanager.hpp"
#include "renderer.hpp"
#include "state.hpp"

class State;
class MenuState;
class GameState;

// Utilizes the "Singleton pattern" to ensure there can only be one game
class Game
{
public:
    static Game* getInstance();

    bool initialize ();
    void exit ();
    void run ();
    
    void popState ();
    void pushState (State *s);
    void changeState (State *s);
    static void pushSettings();
    static void pushNewGame();
    static void pushExit();

    bool isGameExiting();

    Renderer *mRenderer;
    
private:
    static Game *instance;
    Game();
    SDL_Window *mWindow;
    InputManager *mManager;
    std::vector<State*> mStates;

    GameState *mPlayState;
    MenuState *mMainMenuState;
    MenuState *mSettingsState;

    TTF_Font *mFont;
};

#endif // GAME_HPP