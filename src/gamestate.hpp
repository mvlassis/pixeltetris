#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "board.hpp"
#include "inputmanager.hpp"
#include "piece.hpp"
#include "renderer.hpp"
#include "state.hpp"
#include "texture.hpp"

class GameState: public State
{
public:
    GameState (InputManager *manager, Renderer *renderer);
    void initialize() override;
    void exit() override;

    void run() override;
    void update() override;
    void draw() override;
private:
    Board *board;
    Piece currentPiece {0, 0};
    Piece nextPiece {0, 0};
    Piece holdPiece {0, 0};
    Piece ghostPiece {0, 0};
    bool hold_block_first_time;                         // True if the hold block hasn't been used yet
    bool hold_block_used;                               // True if the hold block has been used, resets after a block is placed
   
    Texture *tetrominoSprites;
    SDL_Rect tetrominoSpriteClips[7];
    Texture *playfieldFrame;
    SDL_Rect playfieldFrameClips[4];

    bool isGameOver ();                                 // True if the game has ended
    void createNewPiece();
    void checkState ();                                 // Deletes filled lines and creates a new block.
    void handleEvent (Action action);                   // Handle input
    void movePieceDown ();

    void drawBoard ();
    void drawCurrentPiece (Piece p);
    void drawNextPiece (Piece p);
    void drawHoldPiece (Piece p);
    void drawGhostPiece (Piece p);
    int getRandom (int lower_limit, int upper_limit);   // Return a random number in this range
};

#endif // GAMESTATE_HPP