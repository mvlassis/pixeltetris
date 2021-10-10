#include "optionsstate.hpp"

#include <iostream> // debug
#include "config.hpp"
#include "game.hpp"

OptionsState::OptionsState (InputManager *manager) : State (manager) {}

OptionsState::~OptionsState ()
{
    exit();
}

void OptionsState::initialize ()
{
    index = 0;
    resolution_setting_text = new Texture();
    resolution_setting_text->loadFromText("Resolution", config::default_text_color);
    ghost_block_setting_text = new Texture();
    ghost_block_setting_text->loadFromText("Ghost Block", config::default_text_color);

    texture_on_on = new Texture();
    texture_on_on->loadFromImage("../assets/button-on-on.png");
    texture_on_off = new Texture();
    texture_on_off->loadFromImage("../assets/button-on-off.png");

    texture_off_on = new Texture();
    texture_off_on->loadFromImage("../assets/button-off-on.png");
    texture_off_off = new Texture();
    texture_off_off->loadFromImage("../assets/button-off-off.png");

    mOKButton = new Button("../assets/button-play.png", &Game::goBack, (config::logical_window_width-80)/2, 280);
}

void OptionsState::exit ()
{
    delete resolution_setting_text;
    delete ghost_block_setting_text;
    delete texture_on_on;
    delete texture_on_off;
    delete texture_off_on;
    delete texture_off_off;
    delete mOKButton;
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

    resolution_setting_text->render(50, 100);
    ghost_block_setting_text->render(50, 180);
    if (config::ghost_piece_enabled)
    {
        texture_off_off->render(400, 188);
        texture_on_on->render(500, 188);
    }
    else
    {
        texture_off_on->render(400, 188);
        texture_on_off->render(500, 188);
    }
    mOKButton->draw();
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
        SDL_Rect highlight_box = {mOKButton->getX(), mOKButton->getY(), mOKButton->getWidth(), mOKButton->getHeight()};
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

void OptionsState::changeResolution (SettingChange s)
{
    
}

void OptionsState::changeGhostBlock (SettingChange s)
{
    if (config::ghost_piece_enabled && s == SettingChange::left || !config::ghost_piece_enabled && s == SettingChange::right)
    {
        config::ghost_piece_enabled = !config::ghost_piece_enabled;
    }
}