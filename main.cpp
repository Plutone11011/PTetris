#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Game.h"


//window by reference
bool initSDL(SDL_Window** window) {

    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        success = false ;
    }

    // Create an application window with the following settings:
    *window = SDL_CreateWindow(
        "My Tetris",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (*window == nullptr) {
        // In the case that the window could not be made...
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr ;
    SDL_Event e;

    bool  quit = false ;


    if (!initSDL(&window)) {
        return 1;
    }
    Board GameBoard(window);
    Game tetris;
    StraightLineBuilder straightLineBuilder ;

    tetris.makePiece(&straightLineBuilder);
    //PieceMovement direction = PieceMovement::DOWN ;
    //p.rotate(pivot);
    //p.traslate(direction);



    while (!quit) {

        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        //Clear screen
        GameBoard.clearScreen();

        GameBoard.drawWalls();
//        GameBoard.drawPiece(p);

        GameBoard.renderPresent();
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
