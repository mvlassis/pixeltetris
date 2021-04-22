#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include <SDL2/SDL.h>

#include "texture.hpp"

extern SDL_Renderer *gRenderer;

class Renderer
{  
public:
    void clearScreen ();
    void renderTexture (Texture *texture, int x, int y);
    void updateScreen ();
};


#endif // RENDERER_HPP