#include "Board.h"
#include <algorithm>
//if at least one block of the piece is with a piece either on left or right
bool GameGrid::isColliding(Piece *piece){

    if (piece->getPivotCoords().y >= 0){
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
    }

    for (auto &block: piece->blocks){
        if (block->getCoords().y >= 0){
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

    }
    return false ;
}

bitset<X_AXIS>* GameGrid::getGrid(){
    return grid ;
}

void GameGrid::setOccupiedBlocks(Piece *piece){

    if (piece->pivot->getActive()){
        grid[piece->pivot->getCoords().y].set(piece->pivot->getCoords().x);
    }

    for (auto &block : piece->blocks){
        if (block->getActive()){
            grid[block->getCoords().y].set(block->getCoords().x);
        }

    }

}

ostream& operator<<(ostream & out, const GameGrid & gamegrid){
    for (int i = 0; i < Y_AXIS; i++){
        for (size_t j = 0; j < gamegrid.grid[i].size();j++){
            if (gamegrid.grid[i].test(j)){
                out << 1 ;
            }
            else out << 0 ;
        }
        out << endl ;
    }
    return out ;

}
int GameGrid::isRowFilled(){

    for (int i = 0; i < Y_AXIS; i++){

        if (grid[i].all()){
            //then a row is filled
            return i ;
        }
    }
    return -1 ;
}

Board::Board(SDL_Window *window){

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Board::~Board(){
    SDL_DestroyRenderer(renderer);
}

void Board::drawWalls(){

    SDL_Rect leftwall, rightwall;

    leftwall = { LEFT_WALL_X, 0, WALL_WIDTH, WALL_HEIGTH };
    rightwall = { RIGHT_WALL_X, 0, WALL_WIDTH, WALL_HEIGTH };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x80);
    SDL_RenderFillRect(renderer, &leftwall);
    SDL_RenderFillRect(renderer, &rightwall);
}

void Board::drawGridLines(){

    int verticalLineOffset = LEFT_WALL_X + WALL_WIDTH ;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x0F);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 1; i < X_AXIS; i++){

        SDL_RenderDrawLine(renderer, verticalLineOffset + i*BLOCK_WIDTH, 0, verticalLineOffset + i*BLOCK_WIDTH, SCREEN_HEIGHT);
    }

    for (int i = 1; i < Y_AXIS; i++){

        SDL_RenderDrawLine(renderer, verticalLineOffset, i*BLOCK_HEIGHT, verticalLineOffset + BOARD_WIDTH, i*BLOCK_HEIGHT);
    }
}
void Board::highlightCurrentLines(Piece *piece){
    vector<int> x_values;
    int verticalLineOffset = LEFT_WALL_X + WALL_WIDTH;

    x_values.push_back(piece->pivot->getCoords().x);
    for (auto &block : piece->blocks){
        x_values.push_back(block->getCoords().x);
    }
    int min_x = *min_element(x_values.begin(), x_values.end());
    int max_x = *max_element(x_values.begin(), x_values.end());
    //cout << min_x << "," << max_x << endl ;
    SDL_SetRenderDrawColor(renderer, piece->getColor()->red, piece->getColor()->green, piece->getColor()->blue, 0x0F);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderDrawLine(renderer, verticalLineOffset + BLOCK_WIDTH*min_x, 0, verticalLineOffset + BLOCK_WIDTH*min_x, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, verticalLineOffset + BLOCK_WIDTH*(max_x + 1), 0, verticalLineOffset + BLOCK_WIDTH*(max_x+1), SCREEN_HEIGHT);

    SDL_Rect rect = {verticalLineOffset + (BLOCK_WIDTH * min_x), 0, BLOCK_WIDTH * (max_x - min_x + 1), SCREEN_HEIGHT};
    //SDL_SetRenderDrawColor(renderer, piece->getColor()->red, piece->getColor()->green, piece->getColor()->blue, 0x00);
    SDL_RenderFillRect(renderer, &rect);

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

    SDL_SetRenderDrawColor(renderer, 0x19, 0x28, 0x41, 0x00);//sets color for render
    SDL_RenderClear(renderer);
}

void Board::renderPresent(){
    SDL_RenderPresent(renderer);
}
