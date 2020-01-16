#include "Game.h"

Game::Game(){
    piece_builder = nullptr;
    gameGrid = make_unique<GameGrid>();
}

bool GameGrid::isColliding(int x, int y){

    try{
        return grid[y].test(x);
    }
    catch(const out_of_range& e){
        //the piece bumps against walls or terrain
        return true;
    }
}

void GameGrid::setOccupiedBlocks(Piece *piece){

    grid[piece->pivot->getCoords().y].set(piece->pivot->getCoords().x);

    for (auto &block : piece->blocks){
        grid[block->getCoords().y].set(block->getCoords().x);
    }

}

//builds piece of the type istantiated by the builder
Piece* Game::makePiece(PieceBuilder* piece_builder){

    this->piece_builder = piece_builder;

    this->piece_builder->createPiece();
    this->piece_builder->buildPivot();
    this->piece_builder->buildBlocks();
    this->piece_builder->buildColor();
    Piece* p = this->piece_builder->getPieceMaker() ;

    gameGrid->setOccupiedBlocks(p);
    std::cout << *p  << std::flush ;

    return p ;
}
