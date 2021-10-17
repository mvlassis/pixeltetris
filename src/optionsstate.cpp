#include "optionsstate.hpp"

#include <string>

#include "config.hpp"
#include "game.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

OptionsState::OptionsState (InputManager *manager) : State (manager) {}

OptionsState::~OptionsState ()
{
    exit();
}

void OptionsState::initialize ()
{
    index = 0;
    // Get the current index in the resolution scaling array
    for (int i = 0; i < config::possible_resolution_scalings; i++)
    {
        if (config::resolution_scaling == config::available_resolution_scalings[i])
        {
            resolution_scaling_index = i;
        }
    }
    title_text = new Texture();
    title_text->loadFromText("Options", Game::getInstance()->mRenderer->bigFont, config::default_text_color);
    resolution_setting_text = new Texture();
    resolution_setting_text->loadFromText("Resolution", Game::getInstance()->mRenderer->mediumFont, config::default_text_color);
    resolution_text = new Texture();
    ghost_block_setting_text = new Texture();
    ghost_block_setting_text->loadFromText("Ghost Block", Game::getInstance()->mRenderer->mediumFont, config::default_text_color);

    left_arrow = new Texture();
    right_arrow = new Texture();
    texture_on_on = new Texture();
    texture_on_off = new Texture();
    texture_off_on = new Texture();
    texture_off_off = new Texture();

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    left_arrow->loadFromImage("../../assets/arrow-left.png");
    right_arrow->loadFromImage("../../assets/arrow-right.png");
    texture_on_on->loadFromImage("../../assets/button-on-on.png");
    texture_on_off->loadFromImage("../../assets/button-on-off.png");
    texture_off_on->loadFromImage("../../assets/button-off-on.png");
    texture_off_off->loadFromImage("../../assets/button-off-off.png");
    #else
    left_arrow->loadFromImage("../assets/arrow-left.png");
    right_arrow->loadFromImage("../assets/arrow-right.png");
    texture_on_on->loadFromImage("../assets/button-on-on.png");
    texture_on_off->loadFromImage("../assets/button-on-off.png");
    texture_off_on->loadFromImage("../assets/button-off-on.png");
    texture_off_off->loadFromImage("../assets/button-off-off.png");
    #endif
    
    OKButton = new Button("../assets/button-ok.png", &Game::goBack, (config::logical_window_width-80)/2, 280);
}

void OptionsState::exit ()
{
    delete title_text;
    delete resolution_setting_text;
    delete ghost_block_setting_text;
    delete texture_on_on;
    delete texture_on_off;
    delete texture_off_on;
    delete texture_off_off;
    delete OKButton;
}

void OptionsState::run ()
{
    update();
    draw();
}

void OptionsState::update ()
{
    while (mInputManager->pollAction() != 0)
    {
        if (mInputManager->isGameExiting())
        {
            nextStateID = STATE_EXIT;
            break;
        }
        switch (mInputManager->getAction())
        {
            case Action::back:
            {
                Game::getInstance()->popState();
                break;
            }
            case Action::select:
            {
                if (index == 2)
                {
                    Game::getInstance()->popState();
                }
                break;
            }
            case Action::move_up:
            {
                if (index > 0)
                {
                    --index;
                }
                break;
            }

            case Action::move_down:
            {
                if (index < 2)
                {
                    ++index;
                }
                break;
            }

            case Action::move_left:
            {
                if (index == 0)
                {
                    changeResolution (SettingChange::left);
                }
                else if (index == 1)
                {
                    changeGhostBlock (SettingChange::left);
                }
                break;
            }

            case Action::move_right:
            {
                if (index == 0)
                {
                    changeResolution (SettingChange::right);
                }
                else if (index == 1)
                {
                    changeGhostBlock (SettingChange::right);
                }
                break;
            }

        }
    }
}

void OptionsState::draw ()
{
    Game::getInstance()->mRenderer->clearScreen();

    title_text->renderCentered(config::logical_window_width/2, 50);
    resolution_setting_text->render(50, 100);
    ghost_block_setting_text->render(50, 180);

    std::string resolution_string = std::to_string(int(config::logical_window_width*config::resolution_scaling)) + " x " +
        std::to_string(int(config::logical_window_height*config::resolution_scaling));
    resolution_text->loadFromText (resolution_string, Game::getInstance()->mRenderer->mediumFont, config::default_text_color);
    resolution_text->render(400+(200-resolution_text->getWidth())/2, 101);

    left_arrow->render(383, 105);
    right_arrow->render(590, 105);
    if (config::ghost_piece_enabled)
    {
        texture_off_off->render(400, 188);
        texture_on_on->render(510, 188);
    }
    else
    {
        texture_off_on->render(400, 188);
        texture_on_off->render(510, 188);
    }
    OKButton->draw();
    if (index <= 1)
    {
        int height = resolution_setting_text->getHeight();
        SDL_Rect highlight_box = {0, 100+(index*80), config::logical_window_width, height+5};
        SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor (Game::getInstance()->mRenderer->mSDLRenderer, 255, 255, 255, config::transparency_alpha-20);
        SDL_RenderFillRect(Game::getInstance()->mRenderer->mSDLRenderer, &highlight_box);
        SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_NONE);
    }
    else
    {
        SDL_Rect highlight_box = {OKButton->getX(), OKButton->getY(), OKButton->getWidth(), OKButton->getHeight()};
        SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor (Game::getInstance()->mRenderer->mSDLRenderer, 255, 255, 255, config::transparency_alpha-20);
        SDL_RenderFillRect(Game::getInstance()->mRenderer->mSDLRenderer, &highlight_box);
        SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_NONE);
    }

    Game::getInstance()->mRenderer->updateScreen();
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

// Change the resolution by changing the scaling
void OptionsState::changeResolution (SettingChange s)
{
    if (s == SettingChange::left && resolution_scaling_index > 0)
    {
        --resolution_scaling_index;
        config::resolution_scaling = config::available_resolution_scalings[resolution_scaling_index];
        SDL_SetWindowSize(Game::getInstance()->mWindow, config::logical_window_width*config::available_resolution_scalings[resolution_scaling_index],
            config::logical_window_height*config::available_resolution_scalings[resolution_scaling_index]);
        SDL_SetWindowPosition(Game::getInstance()->mWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
    else if (s == SettingChange::right && resolution_scaling_index < config::possible_resolution_scalings)
    {
        ++resolution_scaling_index;
        config::resolution_scaling = config::available_resolution_scalings[resolution_scaling_index];
        SDL_SetWindowSize(Game::getInstance()->mWindow, config::logical_window_width*config::available_resolution_scalings[resolution_scaling_index],
            config::logical_window_height*config::available_resolution_scalings[resolution_scaling_index]);
        SDL_SetWindowPosition(Game::getInstance()->mWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
}

// Turn the ghost block on or off
void OptionsState::changeGhostBlock (SettingChange s)
{
    if ( s == SettingChange::left && config::ghost_piece_enabled || s == SettingChange::right && !config::ghost_piece_enabled)
    {
        config::ghost_piece_enabled = !config::ghost_piece_enabled;
    }
}