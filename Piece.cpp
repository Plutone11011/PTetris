#include "Piece.h"
//block methods
Block::Block(coordinates block_coords) : block_coords(block_coords), active(true) {}

void Block::setCoords(coordinates c) {
	this->block_coords = c;
}

coordinates Block::getCoords() {
	return this->block_coords;
}

void Block::setActive(bool active){
    this->active = active ;
}

bool Block::getActive(){
    return active ;
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

void Block::inverserotate(coordinates pivot){

    //counterclock-wise rotation matrix is (y, -x) (in SDL coordinate system)
	int relX = this->block_coords.x - pivot.x;
	int relY = this->block_coords.y - pivot.y;
	int tmp;

	tmp = -relX;
	relX = relY;
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
        case PieceMovement::UP:
            this->block_coords.y--;
            break;
        default:
            break ;
    }

}


//setter methods called by builder
void Piece::setPivot(coordinates pivot){

    this->pivot = make_unique<Block>(pivot);

}

void Piece::setBlocks(vector<coordinates> blocks_coords){

	for (auto &coord: blocks_coords) {
		this->blocks.emplace_back(make_unique<Block>(Block(coord)));
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
        if (block->getActive()){
            block->rotate(pivot);
        }
		//std::cout << block->getCoords().x << "," << block->getCoords().y << endl ;
	}
}

void Piece::inverserotate(coordinates pivot) {

	for (auto& block : blocks) {
        if (block->getActive()){
            block->inverserotate(pivot);
        }

		//std::cout << block->getCoords().x << "," << block->getCoords().y << endl ;
	}
}

void Piece::traslate(PieceMovement direction){

    for (auto& block : blocks){
        if (block->getActive()){
            block->traslate(direction);
        }
    }
    pivot->traslate(direction);
}

bool Piece::isOnTheFloor(){

    for (auto& block: blocks){
        if (block->getCoords().y >= Y_AXIS){
            return true ;
        }
    }
    if (pivot->getCoords().y >= Y_AXIS){
        return true ;
    }
    return false ;

}

void Piece::isOverFilledRow(int row){

    if (this->pivot->getCoords().y < row){
        this->pivot->traslate(PieceMovement::DOWN);
    }
    for (auto &block: this->blocks){
        if (block->getCoords().y < row){
            block->traslate(PieceMovement::DOWN);
        }
    }

}
void Piece::blockIsOnFilledRow(int row){

    if (this->pivot->getCoords().y == row){
        this->pivot->setActive(false);
    }
    for (auto &block: this->blocks){
        if (block->getCoords().y == row){
            block->setActive(false);
        }
    }
}

bool Piece::pieceHasToBeDeleted(){
    bool del = true ;
    if (pivot->getActive()){
        del = false ;
    }
    for (auto &block: blocks){
        if (block->getActive()){
            del = false;
        }
    }
    return del ;

}

ostream& operator<<(ostream &out, const Piece& piece){

    out << "Pivot: (" << piece.pivot->getCoords().x << "," << piece.pivot->getCoords().y << ")" << endl ;
    for (auto &block : piece.blocks){
        out << "(" << block->getCoords().x << "," << block->getCoords().y << ")" << endl;
    }
    return out ;
}



