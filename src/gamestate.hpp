#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "board.hpp"
#include "inputmanager.hpp"
#include "piece.hpp"
#include "renderer.hpp"
#include "state.hpp"
#include "texture.hpp"

// The state used when playing a Tetris game
class GameState: public State
{
public:
    GameState (InputManager *manager);
    ~GameState ();
    void initialize() override;
    void exit() override;

    void run() override;
    void update() override;
    void draw() override;

private:
    // Simple enumeration to signify whether the game is starting, in its main phase, or has finished
    enum GamePhase {GAME_STARTED, GAME_PLAYING, GAME_FINISHED};
    GamePhase currentPhase;
    Board *board;
    Piece currentPiece {0, 0};
    Piece nextPiece {0, 0};
    Piece holdPiece {0, 0};
    Piece ghostPiece {0, 0};

    bool hold_block_first_time;                         // True if the hold block hasn't been used yet
    bool hold_block_used;                               // True if the hold block has been used, resets after a block is placed
    bool game_just_started;                             // True if the game has just started or resumed from pause
    unsigned long long time_snap1;                      // Used with time_snap2 to determine when to drop the Tetromino
    unsigned long long time_snap2;
   
    Texture *countdown_texture;
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