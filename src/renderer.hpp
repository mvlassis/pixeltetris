#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "texture.hpp"

extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;


class Renderer
{  
public:
    void clearScreen ();
    void renderTexture (Texture *texture, int x, int y);
    void updateScreen ();
};


#endif // RENDERER_HPP