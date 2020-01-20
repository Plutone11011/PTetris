#pragma once



#include <list>
#include "Board.h"
#include "PieceBuilder.h"
#include "EventHandler.h"

using namespace std;

uint32_t addTimerCallback(uint32_t interval, void* param);

class Game{

private:
    PieceBuilder* piece_builder;
    GameGrid* gameGrid ;
    SDL_TimerID moveTimer ;
    list<unique_ptr<Piece>> pieces;
    unique_ptr<Board> board ;
    EventHandler handler ;
    SDL_Event e ;

    void makePiece(PieceBuilder *piece_builder);


public:
    Game() = default ;
    Game(SDL_Window* window);
    ~Game();

    GameGrid* getGamegrid();

    void createRandomPiece();
    void afterFilledRow(int rowFilled);

    void eventLoop();
    void render();
};


