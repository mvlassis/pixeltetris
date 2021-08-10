#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "config.hpp"
#include "init.hpp"
#include "renderer.hpp"
#include "texture.hpp"

SDL_Window *gWindow = nullptr;
Texture tetrominoSprites;

bool initialize()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initialize SDL! SDL_Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(config::window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        config::logical_window_width, config::logical_window_height, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            std::cerr << "Could not create window! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr)
            {
                std::cerr << "Could not create renderer! SDL_Error: " << SDL_GetError() << '\n';
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                if (IMG_Init(IMG_INIT_PNG) == 0 || IMG_Init(IMG_INIT_JPG) == 0)
                {
                    std::cerr << "Could not initialize SDL_image! SDL_image error: " << IMG_GetError() << '\n';
                }
                if (TTF_Init() == -1)
                {
                    std::cerr << "Could not initialize SDL_ttf! SDL_ttf error: " << TTF_GetError() << '\n';
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    gFont = TTF_OpenFont("../../assets/FiraSans-Regular.ttf", 28);
    tetrominoSprites.loadFromImage("../../assets/tetrominoSprites.png");
    #else
    gFont = TTF_OpenFont("../assets/FiraSans-Regular.ttf", 28);
    tetrominoSprites.loadFromImage("../assets/tetrominoSprites.png");
    #endif
    if (gFont == nullptr)
    {
        std::cerr << "Could not load font! SDL_ttf error: " << TTF_GetError() << '\n';
        success = false;
    }
    return success;
}

void close()
{
    TTF_CloseFont(gFont);
    gFont = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}