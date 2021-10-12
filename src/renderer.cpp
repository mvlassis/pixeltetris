#include "renderer.hpp"

#include <iostream> // For debugging

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "config.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

void Renderer::initialize (SDL_Window *window)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    mFont = TTF_OpenFont("../../assets/munro-small.ttf", 30);
    bigFont = TTF_OpenFont("../../assets/munro.ttf", 50);
    #else
    mediumFont = TTF_OpenFont("../assets/munro-small.ttf", 30);
    bigFont = TTF_OpenFont("../assets/munro.ttf", 50);
    #endif
    if (mediumFont == nullptr || bigFont == nullptr)
    {
        std::cerr << "Could not load font! SDL_ttf error: " << TTF_GetError() << '\n';
    }
    mSDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    clearScreen();
}

Renderer::~Renderer ()
{
    SDL_DestroyRenderer(mSDLRenderer);
    mSDLRenderer = nullptr;
}

void Renderer::clearScreen ()
{
    SDL_SetRenderDrawColor(mSDLRenderer, config::background_r_light, config::background_g_light, config::background_b_light, 0xFF);
    SDL_RenderClear(mSDLRenderer);
}

void Renderer::renderTexture (Texture *texture, int x, int y)
{
    texture->renderCentered(x, y);
}

void Renderer::updateScreen ()
{
    SDL_RenderPresent(mSDLRenderer);
}