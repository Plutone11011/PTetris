#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Game.h"


//window by reference
bool initSDL(SDL_Window*& window) {

    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        success = false ;
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "My Tetris",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == nullptr) {
        // In the case that the window could not be made...
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr ;


    if (!initSDL(window)) {
        return 1;
    }

    Game tetris(window);

    //PieceMovement direction = PieceMovement::DOWN ;
    //p.rotate(pivot);
    //p.traslate(direction);



    while (!quit) {

        tetris.eventLoop();
        tetris.render();

    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
