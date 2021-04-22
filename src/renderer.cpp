#include "renderer.hpp"

#include <iostream> // For debugging

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "config.hpp"

extern TTF_Font *gFont;

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

void Renderer::clearScreen ()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}

void Renderer::renderTexture (Texture *texture, int x, int y)
{
    texture->renderCentered(x, y);
}

void Renderer::updateScreen ()
{
    SDL_RenderPresent(gRenderer);
}