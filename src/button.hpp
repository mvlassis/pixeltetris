#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "texture.hpp"

class Button
{
public:
    Button (std::string path, void (*callback) (), int posX = 0, int posY = 0);
    ~Button ();
    bool loadTexture (std::string path);
    void draw ();
    void (*mCallback) ();

    int getX ();
    int getY ();
    int getWidth ();
    int getHeight ();

private:
    int mPositionX;
    int mPositionY;
    int mWidth;
    int mHeight;
    Texture *mTexture;
};

#endif // BUTTON_HPP