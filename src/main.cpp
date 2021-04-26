#include <iostream>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // needed for the main function WinMain
#include <windows.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "board.hpp"
#include "config.hpp"
#include "gamestate.hpp"
#include "init.hpp"
#include "inputmanager.hpp"
#include "renderer.hpp"
#include "texture.hpp"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	// equivalent to int main() for Windows
#else
int main(int argc, char **argv)
#endif
{
    InputManager *inManager  = new InputManager;
    Board *board = new Board;
    GameState gamestate(board);
    Renderer renderer;
    if (initialize())
    {
        loadMedia();

        gamestate.initializeState();
        gamestate.drawState();
        renderer.updateScreen();

        int countdown = 3;
        Texture countdown_text;
        while (countdown > 0)
        {
            renderer.clearScreen();
            gamestate.drawState();
            countdown_text.loadFromText(std::to_string(countdown), config::default_text_color);
            renderer.renderTexture(&countdown_text, config::logical_window_width/2, config::logical_window_height/2);
            renderer.updateScreen();
            SDL_Delay(1000);
            countdown--;
        }

        inManager->clearEventQueue();
        SDL_Event event;
        unsigned long long time_snap1 = SDL_GetTicks();
        while (!inManager->isGameExiting() && !board->isGameOver())
        {
            while (SDL_PollEvent(&event) != 0)
            {
                inManager->pollAction(event);
                gamestate.handleEvent(inManager->getAction());
            }
            
            unsigned long long time_snap2 = SDL_GetTicks();
            if (time_snap2 - time_snap1 >= config::wait_time)
            {
                gamestate.movePieceDown();
                time_snap1 = SDL_GetTicks();
            }
            renderer.clearScreen();
            gamestate.drawState();
            renderer.updateScreen();
        }

        Texture gameover_text;
        gameover_text.loadFromText("Game Over!", config::default_text_color);
        while (!inManager->isGameExiting())
        {
            while (SDL_PollEvent(&event) != 0)
            {
                inManager->pollAction(event);
            }
                renderer.clearScreen();
                gamestate.drawState();
                renderer.renderTexture(&gameover_text, config::logical_window_width/2, config::logical_window_height/2);
                renderer.updateScreen();
        }
    }
    
    delete inManager;
    delete board;
    std::cerr << "Now exiting!\n";
    close();
    return 0;
}