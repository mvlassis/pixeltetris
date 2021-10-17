#include "pausedstate.hpp"

#include <vector>

#include "config.hpp"
#include "game.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

PausedState::PausedState (InputManager *manager) : State (manager) {}

PausedState::~PausedState ()
{
    exit();
}

void PausedState::initialize ()
{
    index = 1;
    paused_frame = new Texture();
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    paused_frame->loadFromImage("../../assets/paused-frame.png");
    mButtons.push_back(new Button ("../../assets/button-quit.png", &Game::getInstance()->goDoubleBack, 230, 190));
    mButtons.push_back(new Button ("../../assets/button-resume.png", &Game::getInstance()->goBack, 330, 190));
    #else
    paused_frame->loadFromImage("../assets/paused-frame.png");
    mButtons.push_back(new Button ("../assets/button-quit.png", &Game::getInstance()->goDoubleBack, 230, 190));
    mButtons.push_back(new Button ("../assets/button-resume.png", &Game::getInstance()->goBack, 330, 190));
    #endif
}

void PausedState::exit ()
{
    for (auto i : mButtons)
    {
        delete i;
    }
    delete paused_frame;
}

void PausedState::run ()
{
    update();
    draw();
}

void PausedState::update ()
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
            case Action::select:
            {
                mButtons[index]->callbackFunction();
                break;
            }

            case Action::move_left:
            {
                if (index > 0)
                {
                    --index;
                }
                break;
            }

            case Action::move_right:
            {
                if (index < mButtons.size()-1)
                {
                    ++index;
                }
                break;
            }
        }
    }
}

void PausedState::draw ()
{
    paused_frame->renderCentered(config::logical_window_width/2, config::logical_window_height/2);
    for (auto i : mButtons)
    {
        i->draw();
    }
    SDL_Rect highlight_box = {mButtons[index]->getX(), mButtons[index]->getY(), mButtons[index]->getWidth(), mButtons[index]->getHeight()};
    SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor (Game::getInstance()->mRenderer->mSDLRenderer, 255, 255, 255, config::transparency_alpha-20);
    SDL_RenderFillRect(Game::getInstance()->mRenderer->mSDLRenderer, &highlight_box);
    SDL_SetRenderDrawBlendMode (Game::getInstance()->mRenderer->mSDLRenderer, SDL_BLENDMODE_NONE);
    Game::getInstance()->mRenderer->updateScreen();
}