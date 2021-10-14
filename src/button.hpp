#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "texture.hpp"


// Represents a standard button with a texture and a certain position that can be selected. If selected, the callback function can be called
class Button
{
public:
    Button (std::string path, void (*callback) (), int posX = 0, int posY = 0);
    ~Button ();
    bool loadTexture (std::string path);
    void draw ();
    void (*callbackFunction) ();

    int getX ();
    int getY ();
    int getWidth ();
    int getHeight ();

private:
    int position_x;
    int position_y;
    int width;
    int height;
    Texture *texture;
};

#endif // BUTTON_HPP