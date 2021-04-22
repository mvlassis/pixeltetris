#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <queue>

#include "board.hpp"
#include "inputmanager.hpp"
#include "piece.hpp"

class GameState
{
public:
    GameState (Board *b);
    void checkState (); // Deletes filled lines and creates a new block.
    void createNewPiece ();
    void drawState ();
    void handleEvent (Action action);
    void initializeState ();
    void movePieceDown ();
private:
    Board *board;
    Piece currentPiece {0, 0};
    Piece nextPiece {0, 0};
    Piece holdPiece {0, 0};
    std::queue<Piece> nextPieces; // Holds the next 2 pieces

    void drawBoard ();
    void drawPiece (Piece p);
    void drawHoldPiece (Piece p);
    int getRandom (int lower_limit, int upper_limit); // Return a random number in this range
};


#endif // GAMESTATE_HPP