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
    void initializeState ();                            // Create new board and load necessary textures
    bool isGameOver ();                                 // True if the game has ended
    void movePieceDown ();
private:
    bool hold_block_first_time;                         // True if the hold block hasn't been used yet
    bool hold_block_used;                               // True if the hold block has been used, resets after a block is placed
    Board *board;
    Piece currentPiece {0, 0};
    Piece ghostPiece {0, 0};
    Piece holdPiece {0, 0};
    Piece nextPiece {0, 0};
    std::queue<Piece> nextPieces;                       // Holds the next 2 pieces
    Texture tetrominoSprites;
    SDL_Rect tetrominoSpriteClips[7];
    Texture playfieldFrame;
    SDL_Rect playfieldFrameClips[4];

    void drawBoard ();
    void drawCurrentPiece (Piece p);
    void drawGhostPiece (Piece p);
    void drawHoldPiece (Piece p);
    void drawNextPiece (Piece p);
    int getRandom (int lower_limit, int upper_limit);   // Return a random number in this range
};


#endif // GAMESTATE_HPP