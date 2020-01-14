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
	//then use rotation matrix with 90° (-y,x)
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

//piece methods
/*Piece::Piece(Piece&& piece) noexcept : blocks(move(piece.blocks)), pivot(move(piece.pivot)) {}
Piece& Piece::operator=(Piece&& piece) noexcept {
	if (&piece == this) {
		//self assignment
		return *this;
	}
	blocks = move(piece.blocks);
	pivot = move(piece.pivot);
	return *this;
}*/

Piece makePiece(coordinates pivot, coordinates* block , unsigned int length) {
	Piece piece(pivot, block,length);
	return piece;
}


Piece::Piece(coordinates pivot, coordinates *block, unsigned int length) {

	this->pivot = make_unique<Block>(pivot);
	coordinates* ptr = block;
	for (ptr; ptr < (block + length); ++ptr) {
		this->blocks.emplace_back(make_unique<Block>(Block(*ptr)));
	}
}

//rotates every piece except pivot and traslates every piece
void Piece::rotate(coordinates pivot) {

	for (auto& block : blocks) {
		block->rotate(pivot);
	}
}

void Piece::traslate(PieceMovement direction){

    for (auto& block : blocks){
        block->traslate(direction);
    }
    pivot->traslate(direction);
}
