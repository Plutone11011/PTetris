#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>

using namespace std;

struct coordinates {

	int x;
	int y;

};

class PieceComponent {

public:
	//factory method
	//static Piece* makePiece(vector<Block>& blocks);
	virtual void rotate(coordinates pivot) = 0;
};

//single block with coordinates
class Block : public PieceComponent {

private:
	coordinates block_coords;

public:
	Block() = default;
	Block(coordinates block_coords);

	coordinates getCoords();
	void setCoords(coordinates);
	//default copy and assignment constructors
	void rotate(coordinates pivot);

	~Block() = default;
};



class Piece : public PieceComponent {
//Composite of blocks
protected:
	unique_ptr<Block> pivot;//smart pointer, self-manages freeing memory when out of scope
	vector<unique_ptr<Block>> blocks;
public:
	//Piece();
	Piece(coordinates pivot, coordinates *block, unsigned int length);

	Piece(const Piece&) = delete;//no copy constructor or assignment
	Piece& operator= (const Piece&) = delete;

	Piece(Piece&&) = default;
	Piece& operator = (Piece&&) = default;

	~Piece() = default;

	void rotate(coordinates pivot);
};
//rvalue for move constructor
Piece makePiece(coordinates pivot, coordinates* block, unsigned int length);

#endif
