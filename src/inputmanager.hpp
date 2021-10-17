#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SDL2/SDL.h>

// A simple enumeration to hold all possible actions when playing.
enum class Action
{
    stay_idle, back, move_up, move_down, move_left, move_right, select, drop, rotate, hold, pause
};

// Manages all input polled from the keyboard
class InputManager
{
public:
    InputManager ();
    void clearEventQueue ();
    Action getAction ();
    bool isGameExiting ();
    bool pollAction ();
    void setExit ();
private:
    bool quit_game;
    Action action;
};

#endif // INPUTMANAGER_HPP