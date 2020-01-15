#pragma once

#include <bitset>
#include "Board.h"


using namespace std;


class Game{

private:
    //an array of bitset to represent each position
    //as either busy or not in the game board
    bitset<X_AXIS> grid[Y_AXIS];
    PieceBuilder* piece_builder;
public:
    Game() = default ;

    bool isColliding(int x, int y);

    Piece* makePiece(PieceBuilder *piece_builder);
};
