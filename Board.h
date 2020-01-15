#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include "Piece.h"



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
