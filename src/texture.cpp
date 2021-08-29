#include "texture.hpp"

#include <iostream>

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL_image.h"

#include "config.hpp"
#include "renderer.hpp"

extern TTF_Font *gFont;

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Texture::Texture() {mTexture = nullptr;}

Texture::Texture(Renderer *renderer)
{
    mRenderer = renderer;
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

void Texture::loadFromImage (std::string path) 
{
    free();
    SDL_Surface *tempSurf = IMG_Load(path.c_str());
    if (tempSurf == nullptr)
    {
        std::cerr << "Texture: Could not load image from path: " << path << '\n';
    }
    else
    {
        // SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB(tempSurf->format, 0xFE, 0xFE, 0xFE)); 
        mTexture = SDL_CreateTextureFromSurface(mRenderer->mSDLRenderer, tempSurf);
        width = tempSurf->w;
        height = tempSurf->h;
        SDL_FreeSurface(tempSurf);
    }
}

// Creates texture from string with a certain color
void Texture::loadFromText (std::string text, SDL_Color text_color)
{
    free();
    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(mRenderer->mFont, text.c_str(), text_color, config::logical_window_width);
    if (text_surface == nullptr)
    {
        std::cerr << "Could not create surface from text! SDL_ttf error: " << TTF_GetError() << '\n';
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(mRenderer->mSDLRenderer, text_surface);
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
void Texture::render (int x, int y, SDL_Rect *clip)
{
    SDL_Rect r = {x, y, width, height};
    if (clip != nullptr)
    {
        r.w = clip->w;
        r.h = clip->h;
    }
    SDL_RenderCopy(mRenderer->mSDLRenderer, mTexture, clip, &r);
}

// Renders texture centered at x, y
void Texture::renderCentered (int x, int y)
{
    SDL_Rect r = {x-(width/2), y-(height/2), width, height};
    SDL_RenderCopy(mRenderer->mSDLRenderer, mTexture, nullptr, &r);
}

void Texture::setAlphaMode (Uint8 alpha)
{
    SDL_SetTextureAlphaMod (mTexture, alpha);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}