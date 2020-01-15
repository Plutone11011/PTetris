#include "Game.h"

bool Game::isColliding(int x, int y){

    try{
        return grid[y].test(x);
    }
    catch(const out_of_range& e){
        //the piece bumps against walls or terrain
        return true;
    }
}

void Game::makePiece(PieceBuilder* piece_builder){

    this->piece_builder = piece_builder;

    this->piece_builder->createPiece();
    this->piece_builder->buildPivot();
    Piece* p = this->piece_builder->getPieceMaker() ;
    std::cout << *p ;
}
