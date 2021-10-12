#ifndef PAUSEDSTATE_HPP
#define PAUSEDSTATE_HPP

#include "button.hpp"
#include "inputmanager.hpp"
#include "state.hpp"

class PausedState: public State
{
public:
    PausedState (InputManager *manager);
    ~PausedState ();
    void initialize () override;
    void exit () override;

    void run () override;
    void update () override;
    void draw () override;

private:
    std::vector<Button*> mButtons;
    Texture *paused_frame;

    int index;                  // Shows the current button selected
};

#endif // PAUSEDSTATE_HPP