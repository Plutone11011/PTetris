#include "Piece.h"
//block methods
Block::Block(coordinates block_coords) : block_coords(block_coords) {}

void Block::setCoords(coordinates c) {
	this->block_coords = c;
}

coordinates Block::getCoords() {
	return this->block_coords;
}

void Block::rotate(coordinates pivot) {

	//compute relative coordinates to pivot
	//then use rotation matrix with 90� (-y,x)
	//and sum to pivot coordinates

	int relX = this->block_coords.x - pivot.x;
	int relY = this->block_coords.y - pivot.y;
	int tmp;

	tmp = relX;
	relX = -relY;
	relY = tmp ;

	this->block_coords.x = relX + pivot.x;
	this->block_coords.y = relY + pivot.y;
}

void Block::traslate(PieceMovement direction){

    switch(direction){

        case PieceMovement::DOWN:
            this->block_coords.y++;
            break;
        case PieceMovement::LEFT:
            this->block_coords.x--;
            break;
        case PieceMovement::RIGHT:
            this->block_coords.x++;
            break ;
        default:
            break ;
    }

}


//setter methods called by builder
void Piece::setPivot(coordinates pivot){

    this->pivot = make_unique<Block>(pivot);

}

void Piece::setBlocks(coordinates* blocks_coords, unsigned int length){

    coordinates* ptr = blocks_coords ;
	for (ptr; ptr < (blocks_coords + length); ++ptr) {
		this->blocks.emplace_back(make_unique<Block>(Block(*ptr)));
	}
}

void Piece::setColor(const rgb& color){
    this->color = color ;
}

rgb* Piece::getColor(){
    return &color;
}

coordinates Piece::getPivotCoords(){
    return pivot->getCoords() ;
}
/*Piece movements*/

//rotates every piece except pivot and traslates every piece
void Piece::rotate(coordinates pivot) {

	for (auto& block : blocks) {
		block->rotate(pivot);
		//std::cout << block->getCoords().x << "," << block->getCoords().y << endl ;
	}
}

void Piece::traslate(PieceMovement direction){

    for (auto& block : blocks){
        block->traslate(direction);
    }
    pivot->traslate(direction);
}

ostream& operator<<(ostream &out, const Piece& piece){

    out << "Pivot: (" << piece.pivot->getCoords().x << "," << piece.pivot->getCoords().y << ")" << endl ;
    for (auto &block : piece.blocks){
        out << "(" << block->getCoords().x << "," << block->getCoords().y << ")" << endl;
    }
    return out ;
}



