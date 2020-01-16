#pragma once

#include <bitset>
#include "Board.h"
#include "PieceBuilder.h"

using namespace std;

class GameGrid{

private:
    //an array of bitset to represent each position
    //as either busy or not in the game board
    bitset<X_AXIS> grid[SCREEN_HEIGHT];

public:
    GameGrid() = default ;

    bool isColliding(int x, int y);
    void setOccupiedBlocks(Piece *piece);

    ~GameGrid()=default ;

};

class Game{

private:
    PieceBuilder* piece_builder;
    unique_ptr<GameGrid> gameGrid ;
public:
    Game();

    Piece* makePiece(PieceBuilder *piece_builder);
};


