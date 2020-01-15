#include "Board.h"

Board::Board(SDL_Window *window){

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Board::~Board(){
    SDL_DestroyRenderer(renderer);
}

void Board::drawWalls(){

    SDL_Rect leftwall, rightwall;

    leftwall = { LEFT_WALL_X, LEFT_WALL_Y, WALL_WIDTH, WALL_HEIGTH };
    rightwall = { RIGHT_WALL_X, RIGHT_WALL_Y, WALL_WIDTH, WALL_HEIGTH };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &leftwall);
    SDL_RenderFillRect(renderer, &rightwall);
}

void Board::drawPiece(const Piece& piece){


    SDL_Rect rblock;

    //draws each block of the piece
    rblock = {LEFT_WALL_X + WALL_WIDTH + (BLOCK_WIDTH*piece.pivot->getCoords().x), LEFT_WALL_Y + (BLOCK_HEIGHT*piece.pivot->getCoords().y) ,BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rblock);


    for (auto& block : piece.blocks){
        rblock = {LEFT_WALL_X + WALL_WIDTH + (BLOCK_WIDTH*block->getCoords().x), LEFT_WALL_Y + (BLOCK_HEIGHT*block->getCoords().y) ,BLOCK_WIDTH, BLOCK_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rblock);
    }
}


void Board::clearScreen(){

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);//sets color for render
    SDL_RenderClear(renderer);
}

void Board::renderPresent(){
    SDL_RenderPresent(renderer);
}
