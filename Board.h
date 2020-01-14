#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include "Piece.h"

#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1280
#define LEFT_WALL_X 200
#define LEFT_WALL_Y 180
#define WALL_WIDTH 30
#define WALL_HEIGTH (SCREEN_HEIGHT - LEFT_WALL_Y)
#define BOARD_WIDTH 820
#define BOARD_HEIGHT WALL_HEIGTH
#define RIGHT_WALL_X (SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH)
#define RIGHT_WALL_Y LEFT_WALL_Y

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

    void drawPiece(const Piece& piece);

    void clearScreen();

    void renderPresent();
};
