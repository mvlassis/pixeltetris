#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <queue>

#include "board.hpp"
#include "inputmanager.hpp"
#include "piece.hpp"
#include "texture.hpp"

class GameState
{
public:
    GameState ();
    void checkState ();                                 // Deletes filled lines and creates a new block.
    void createNewPiece ();                             // Create a new random piece
    void drawState ();                                  // Draw the board and all pieces after each frame
    void handleEvent (Action action);                   // Handle input
    void initializeState ();
    bool isGameOver ();                                 // True if the game has ended
    void movePieceDown ();
private:
    Board *board;
    Piece currentPiece {0, 0};
    Piece nextPiece {0, 0};
    Piece holdPiece {0, 0};
    std::queue<Piece> nextPieces;                       // Holds the next 2 pieces
    Texture tetrominoSprites;
    SDL_Rect tetrominoSpriteClips[7];

    void drawBoard ();
    void drawPiece (Piece p);
    void drawHoldPiece (Piece p);
    int getRandom (int lower_limit, int upper_limit);   // Return a random number in this range
};


#endif // GAMESTATE_HPP