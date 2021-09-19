#include "menustate.hpp"

#include <vector>

#include <SDL2/SDL.h>

#include "config.hpp"
#include "inputmanager.hpp"
#include "renderer.hpp"
#include "state.hpp"

MenuState::MenuState (InputManager *manager) : State (manager) {}

MenuState::~MenuState ()
{
    exit();
}

void MenuState::initialize()
{
    index = 0;
}

void MenuState::exit()
{
    for (auto i : mButtons)
    {
        delete i;
    }
}

void MenuState::run()
{
    update();
    draw();          
}

void MenuState::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        mInputManager->pollAction(event);
        if (mInputManager->isGameExiting())
        {
            nextStateID = STATE_EXIT;
            break;
        }
        switch (mInputManager->getAction())
        {
            case Action::select:
            {
                mButtons[index]->mCallback();
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
                if (index < mButtons.size())
                {
                    ++index;
                }
                break;
            }
        }
    }
}

void MenuState::draw()
{
    Game::getInstance()->mRenderer->clearScreen();
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

void MenuState::addButton (Button *button)
{
    mButtons.push_back(button);
}