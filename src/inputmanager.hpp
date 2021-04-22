#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SDL2/SDL.h>

// A simple enumeration to hold all possible actions for a piece.
enum class Action
{
    stay_idle, move_down, move_left, move_right, drop, rotate
};

class InputManager
{
public:
    void clearEventQueue();
    Action getAction();
    bool isGameExiting();
    void pollAction(SDL_Event event);
    void setExit();
private:
    bool quit_game = false;
    Action action = Action::stay_idle;
};

#endif // INPUTMANAGER_HPP