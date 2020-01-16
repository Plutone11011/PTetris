#include <ctime>
#include <cstdlib>
#include "PieceBuilder.h"

void PieceBuilder::createPiece(){
    piece_maker = make_unique<Piece>();
}

Piece* PieceBuilder::getPieceMaker(){
    return piece_maker.get();
}

void PieceBuilder::buildPivot(){

    srand(time(nullptr));

    int x = 10 + (rand() % (X_AXIS - 20)); //offset to make sure they don't spawn outside of board horizontally
    int y = 10 + (rand() % (Y_AXIS_BEFORE_WALL - 20)) ;//offset to make sure they spawn over the walls, but not outside window

    coordinates pivot{x,y} ;

    piece_maker->setPivot(pivot);


}
/*From here, builder of each piece type*/

//Precondition: buildPivot has already been called
void StraightLineBuilder::buildBlocks(){

    //****
    coordinates blocks[3] = {{piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y} };

    piece_maker->setBlocks(blocks, 3);

}

void StraightLineBuilder::buildColor(){
    piece_maker->setColor({0x00, 0xFF, 0xFF});
}


void InverseLBuilder::buildBlocks(){

    coordinates blocks[3] = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks, 3);
}

void InverseLBuilder::buildColor(){
    piece_maker->setColor({0x00, 0x00, 0xFF});
}

void RightLBuilder::buildBlocks(){
    coordinates blocks[3] = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y + 1},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x - 2, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks, 3);
}

void RightLBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0xA5, 0x00});
}

void SquareBuilder::buildBlocks(){
    coordinates blocks[3] = {{piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y}};

    piece_maker->setBlocks(blocks, 3);
}

void SquareBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0xFF, 0x00});
}

void RhodeIslandBuilder::buildBlocks(){

    coordinates blocks[3] = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x + 2, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks, 3);
}

void RhodeIslandBuilder::buildColor(){
    piece_maker->setColor({0x00, 0xFF, 0x00});
}

void WasdBuilder::buildBlocks(){

    coordinates blocks[3] = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y}, {piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks, 3);
}

void WasdBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0x00, 0xFF});
}

void LightningBoltBuilder::buildBlocks(){
    coordinates blocks[3] = {{piece_maker->getPivotCoords().x + 1, piece_maker->getPivotCoords().y},
    {piece_maker->getPivotCoords().x - 1, piece_maker->getPivotCoords().y - 1}, {piece_maker->getPivotCoords().x, piece_maker->getPivotCoords().y - 1}};

    piece_maker->setBlocks(blocks, 3);
}

void LightningBoltBuilder::buildColor(){
    piece_maker->setColor({0xFF, 0x00, 0x00});
}
