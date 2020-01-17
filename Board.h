#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <bitset>
#include "Piece.h"

class GameGrid{

private:
    //an array of bitset to represent each position
    //as either busy or not in the game board
    bitset<X_AXIS> grid[SCREEN_HEIGHT];

public:
    GameGrid() = default ;

    bool isColliding(int x, int y);
    void setOccupiedBlocks(Piece *piece);

    bitset<X_AXIS>* getGrid();

    ~GameGrid()=default ;
};

//sort of adapter of renderer
class Board{
private:
    SDL_Renderer *renderer ;

public:
    Board() = default;
    Board(SDL_Window *window);
    ~Board();

    //no need for copy constructor and assignment or move semantics
    Board(const Board&) = delete ;
    Board& operator=(const Board&) = delete ;

    Board(Board&&) = delete ;
    Board& operator=(Board&&) = delete ;

    void drawWalls();
    void drawPiece(Piece* piece);

    void clearScreen();

    void renderPresent();
};
