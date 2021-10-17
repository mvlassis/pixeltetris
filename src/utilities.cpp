#include "utilities.hpp"

#include "piece.hpp"

// Simple function to swap two pieces
void swap(Piece &a, Piece &b)
{
    Piece temp = a;
    a = b;
    b = temp;
}