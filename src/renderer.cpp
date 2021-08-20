#include "renderer.hpp"

#include <iostream> // For debugging

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "config.hpp"

TTF_Font *gFont = nullptr;

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

void Renderer::initialize (SDL_Window *window)
{
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