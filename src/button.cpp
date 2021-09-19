#include "button.hpp"

#include <iostream> // debug
#include <string>

Button::Button (std::string path, void (*callback) (), int posX, int posY)
{
    mCallback = callback;
    mPositionX = posX;
    mPositionY = posY;
    mTexture = new Texture;
    mTexture->loadFromImage(path);
    mWidth = mTexture->getWidth();
    mHeight = mTexture->getHeight();
}

Button::~Button ()
{
    mTexture->free();
}

void Button::draw ()
{
    mTexture->render(mPositionX, mPositionY);
}

int Button::getX ()
{
    return mPositionX;
}

int Button::getY ()
{
    return mPositionY;
}

int Button::getWidth ()
{
    return mWidth;
}

int Button::getHeight ()
{
    return mHeight;
}