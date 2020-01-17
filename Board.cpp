#include "Board.h"

//if at least one block of the piece is colliding then return true
bool GameGrid::isColliding(Piece *piece){

    try{
        if(grid[piece->getPivotCoords().y].test(piece->getPivotCoords().x)){
            return true ;
        }

    }
    catch(const out_of_range& e){
        cout << piece->getPivotCoords().x << "," << piece->getPivotCoords().y << endl;
        //the piece bumps against walls or terrain
        return true;
    }
    for (auto &block: piece->blocks){
        try{
            if (grid[block->getCoords().y].test(block->getCoords().x)){
                return true;
            }
        }
        catch(const out_of_range& e){
            cout << block->getCoords().x << "," << block->getCoords().y << endl;
            //the piece bumps against walls or terrain
            return true;
        }
    }
    return false ;
}

bitset<X_AXIS>* GameGrid::getGrid(){
    return grid ;
}

void GameGrid::setOccupiedBlocks(Piece *piece){

    grid[piece->pivot->getCoords().y].set(piece->pivot->getCoords().x);

    for (auto &block : piece->blocks){
        grid[block->getCoords().y].set(block->getCoords().x);
    }

}

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


void Board::drawPiece(Piece* piece){


    SDL_Rect rblock;

    //draws each block of the piece if active
    if (piece->pivot->getActive()){
        rblock = {LEFT_WALL_X + WALL_WIDTH + (BLOCK_WIDTH * piece->pivot->getCoords().x),BLOCK_HEIGHT * piece->pivot->getCoords().y ,BLOCK_WIDTH, BLOCK_HEIGHT};
        SDL_SetRenderDrawColor(renderer, piece->getColor()->red, piece->getColor()->green, piece->getColor()->blue, 0xFF);
        SDL_RenderFillRect(renderer, &rblock);
    }



    for (auto& block : piece->blocks){
        if (block->getActive()){
            rblock = {LEFT_WALL_X + WALL_WIDTH + (BLOCK_WIDTH*block->getCoords().x),BLOCK_HEIGHT*block->getCoords().y ,BLOCK_WIDTH, BLOCK_HEIGHT};
            SDL_SetRenderDrawColor(renderer, piece->getColor()->red, piece->getColor()->green, piece->getColor()->blue, 0xFF);
            SDL_RenderFillRect(renderer, &rblock);
        }

    }
}


void Board::clearScreen(){

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);//sets color for render
    SDL_RenderClear(renderer);
}

void Board::renderPresent(){
    SDL_RenderPresent(renderer);
}
