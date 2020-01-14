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
#define RIGHT_WALL_X (SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH)
#define RIGHT_WALL_Y LEFT_WALL_Y

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
    SDL_Renderer* renderer = nullptr;
    bool winning_condition = false, quit = false ;


    if (!initSDL(&window)) {
        return 1;
    }

    coordinates pivot = { 2,3 };
    coordinates blocks[]{ { 2,2 } , { 3,3 } , { 3,4 } };

    Piece p = makePiece(pivot, blocks, 3);
    //Piece p(move(pivot), blocks);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);//sets color for render
        SDL_RenderClear(renderer);

        //Render tetris walls
        SDL_Rect leftwall, rightwall;
        leftwall = { LEFT_WALL_X, LEFT_WALL_Y, WALL_WIDTH, WALL_HEIGTH };
        rightwall = { RIGHT_WALL_X, RIGHT_WALL_Y, WALL_WIDTH, WALL_HEIGTH };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &leftwall);
        SDL_RenderFillRect(renderer, &rightwall);

        SDL_RenderPresent(renderer);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
