#ifndef OPTIONSSTATE_HPP
#define OPTIONSSTATE_HPP

#include <vector>

#include "button.hpp"
#include "inputmanager.hpp"
#include "state.hpp"

class OptionsState: public State
{
    // Enumeration used when change a setting
    enum class SettingChange {left, right};
public:
    OptionsState (InputManager *inputmanager);
    ~OptionsState ();
    void initialize () override;
    void exit () override;

    void run () override;
    void update () override;
    void draw () override;

private:
    Button *OKButton;
    Texture *title_text;
    Texture *resolution_setting_text;
    Texture *resolution_text;
    Texture *left_arrow;
    Texture *right_arrow;
    Texture *ghost_block_setting_text;
    Texture *texture_on_on;
    Texture *texture_on_off;
    Texture *texture_off_on;
    Texture *texture_off_off;
    int index;
    int resolution_scaling_index;                   // Current index of the resolution scaling in the config::available_resolution_scalings array

    void changeResolution (SettingChange s);
    void changeGhostBlock (SettingChange s);
};

#endif // OPTIONSSTATE_HPP