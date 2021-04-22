#include "texture.hpp"

#include <iostream>

#include "SDL2/SDL_ttf.h"

#include "config.hpp"

extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Texture::Texture()
{
    mTexture = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        width = 0;
        height = 0;
    }
}

// Creates texture from string with a certain color
void Texture::loadFromText (std::string text, SDL_Color text_color)
{
    free();
    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(gFont, text.c_str(), text_color, config::logical_window_width);
    if (text_surface == nullptr)
    {
        std::cerr << "Could not create surface from text! SDL_ttf error: " << TTF_GetError() << '\n';
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
        if (mTexture == nullptr)
        {
            std::cerr << "Could not create texture from rendered text! SDL error: " << SDL_GetError() << '\n';
        }
        else
        {
            width = text_surface->w;
            height = text_surface->h;
        }
    }
    SDL_FreeSurface(text_surface);
}

// Renders texture with top left corner at x, y
void Texture::render (int x, int y)
{
    SDL_Rect r = {x, y, width, height};
    SDL_RenderCopy(gRenderer, mTexture, &r, nullptr);
}

// Renders texture centered at x, y
void Texture::renderCentered (int x, int y)
{
    SDL_Rect r = {x-(width/2), y-(height/2), width, height};
    SDL_RenderCopy(gRenderer, mTexture, nullptr, &r);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}