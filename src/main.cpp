#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // needed for the main function WinMain
#include <windows.h>
#endif

#include "game.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	// equivalent to int main() for Windows
#else
int main(int argc, char **argv)
#endif
{
    Game game;
    game.run();
    return 0;
}