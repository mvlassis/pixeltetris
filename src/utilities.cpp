#include "utilities.hpp"

#include "piece.hpp"

void swap(Piece &a, Piece &b)
{
    Piece temp = a;
    a = b;
    b = temp;
}