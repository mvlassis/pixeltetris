#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "inputmanager.hpp"
#include "renderer.hpp"
#include "state.hpp"

class MenuState: public State
{
public:
    MenuState (InputManager *manager);
    void initialize () override;
    void exit () override;
    
    void run () override;
    void update () override;
    void draw () override;
};

#endif // MENUTATE_HPP