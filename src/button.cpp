#include "button.hpp"

#include <string>

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Button::Button (std::string path, void (*callback) (), int posX, int posY)
{
    callbackFunction = callback;
    position_x = posX;
    position_y = posY;
    texture = new Texture;
    texture->loadFromImage(path);
    width = texture->getWidth();
    height = texture->getHeight();
}

Button::~Button ()
{
    texture->free();
}

// Draws the button on the screen
void Button::draw ()
{
    texture->render(position_x, position_y);
}

int Button::getX ()
{
    return position_x;
}

int Button::getY ()
{
    return position_y;
}

int Button::getWidth ()
{
    return width;
}

int Button::getHeight ()
{
    return height;
}