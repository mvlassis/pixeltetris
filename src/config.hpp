#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SDL2/SDL.h>

namespace config
{   
    // Window title
    const char window_title[] = "Tetris!";

    // Logical resolution of the game. Most constants are in respect to these two values,
    // so do not change them unless you know what you're doing
    const int logical_window_width = 640;
    const int logical_window_height = 360;

    // Board class
    const int width_to_playfield = 245;       // in pixels
    const int height_to_playfield = 30;       // in pixels
    const int block_size = 15;                // in pixels
    const int playfield_width = 10;           // in blocks
    const int playfield_height = 20;          // in blocks
    const int frame_width = 5;                // frame that surrounds the playfield; in pixels
    const int board_height = 50;              // distance from botton where the playfield begins; in pixels
    const int matrix_blocks = 5;              // matrix that holds tetromino info; in blocks


    // GameState class
    const int next_box_x = 405;               // Horizontal distance from top left corner; in pixels
    const int next_box_y = 10;                // Horizontal distance from top left corner; in pixels

    const int hold_box_x = 150;               // Horizontal distance from top left corner; in pixels
    const int hold_box_y = 10;                // Vertical distance from top left corner; in pixels

    // Constants relating to Tetris
    const int wait_time = 1000;               // Time in milliseconds

    // Visuals
    const SDL_Color default_text_color = {0x00, 0x00, 0x00, 0xFF}; // Default color for all text
}

#endif // CONFIG_HPP