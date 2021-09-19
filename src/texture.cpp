#include "texture.hpp"

#include <iostream>

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL_image.h"

#include "config.hpp"
#include "game.hpp"
#include "renderer.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Texture::Texture() {mTexture = nullptr;}

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

bool Texture::loadFromImage (std::string path) 
{
    bool success = true;
    free();
    SDL_Surface *tempSurf = IMG_Load(path.c_str());
    if (tempSurf == nullptr)
    {
        std::cerr << "Texture: Could not load image from path: " << path << '\n';
        success = false;
    }
    else
    {
        // SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB(tempSurf->format, 0xFE, 0xFE, 0xFE)); 
        mTexture = SDL_CreateTextureFromSurface(Game::getInstance()->mRenderer->mSDLRenderer, tempSurf);
        width = tempSurf->w;
        height = tempSurf->h;
        SDL_FreeSurface(tempSurf);
    }
    return success;
}

// Creates texture from string with a certain color
bool Texture::loadFromText (std::string text, SDL_Color text_color)
{
    bool success = true;
    free();
    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(Game::getInstance()->mRenderer->mFont, text.c_str(), text_color, config::logical_window_width);
    if (text_surface == nullptr)
    {
        std::cerr << "Could not create surface from text! SDL_ttf error: " << TTF_GetError() << '\n';
        success = false;
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(Game::getInstance()->mRenderer->mSDLRenderer, text_surface);
        if (mTexture == nullptr)
        {
            std::cerr << "Could not create texture from rendered text! SDL error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            width = text_surface->w;
            height = text_surface->h;
        }
    }
    SDL_FreeSurface(text_surface);
    return success;
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
    SDL_RenderCopy(Game::getInstance()->mRenderer->mSDLRenderer, mTexture, clip, &r);
}

// Renders texture centered at x, y
void Texture::renderCentered (int x, int y)
{
    SDL_Rect r = {x-(width/2), y-(height/2), width, height};
    SDL_RenderCopy(Game::getInstance()->mRenderer->mSDLRenderer, mTexture, nullptr, &r);
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