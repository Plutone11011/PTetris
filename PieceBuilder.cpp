#include <ctime>
#include <cstdlib>
#include "PieceBuilder.h"

void PieceBuilder::createPiece(){
    piece_maker = make_unique<Piece>();
}

Piece* PieceBuilder::getPiece(){
    return piece_maker.get();
}

unique_ptr<Piece> PieceBuilder::getPieceMaker(){
    return move(piece_maker);
}

void PieceBuilder::buildPivot(){

    srand(time(nullptr));

    int x = 10 + (rand() % (X_AXIS - 20)); //offset to make sure they don't spawn outside of board horizontally
    int y = rand() % 10;

    coordinates pivot{x,y} ;

    piece_maker->setPivot(pivot);


}
/*From here, builder of each piece type*/

//Precondition: buildPivot has already been called
void StraightLineBuilder::buildBlocks(){

    //****
    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y} };

    piece_maker->setBlocks(blocks);

}

void StraightLineBuilder::buildColor(){
    piece_maker->setColor({0x00, 0xFF, 0xFF});
}


void InverseLBuilder::buildBlocks(){

    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks);
}

void InverseLBuilder::buildColor(){
    piece_maker->setColor({0x00, 0x00, 0xFF});
}

void RightLBuilder::buildBlocks(){
    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x - 2, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks);
}

void RightLBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0xA5, 0x00});
}

void SquareBuilder::buildBlocks(){
    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks);
}

void SquareBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0xFF, 0x00});
}

void RhodeIslandBuilder::buildBlocks(){

    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks);
}

void RhodeIslandBuilder::buildColor(){
    piece_maker->setColor({0x00, 0xFF, 0x00});
}

void WasdBuilder::buildBlocks(){

    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks);
}

void WasdBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0x00, 0xFF});
}

void LightningBoltBuilder::buildBlocks(){
    vector<coordinates> blocks = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks);
}

void LightningBoltBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0x00, 0x00});
}
