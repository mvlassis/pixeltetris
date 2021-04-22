#ifndef INIT_HPP
#define INIT_HPP

#include <SDL2/SDL.h>

// Initializes game; returns true on success, false on failure
bool initialize();

// Loads all fonts we will be using
bool loadMedia();

// Shuts down all SDL subsystems, frees memory and closes window
void close();

#endif // INIT_HPP