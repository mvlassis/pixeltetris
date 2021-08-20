#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "texture.hpp"

class Renderer
{  
public:
    void initialize (SDL_Window *window);
    ~Renderer();

    void clearScreen ();
    void renderTexture (Texture *texture, int x, int y);
    void updateScreen ();
    SDL_Renderer *mSDLRenderer;
private:
};


#endif // RENDERER_HPP