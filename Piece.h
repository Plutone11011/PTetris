#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <ostream>
#include <iostream>

#define BLOCK_WIDTH 10
#define BLOCK_HEIGHT 10
#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1280
#define X_AXIS (SCREEN_WIDTH / BLOCK_WIDTH)
#define Y_AXIS (SCREEN_HEIGHT / BLOCK_HEIGHT)
#define LEFT_WALL_Y 180

using namespace std;

struct coordinates {

	int x;
	int y;

};

enum class PieceMovement { LEFT, RIGHT, DOWN };
enum class PieceTypes {STRAIGHT_LINE, INVERSE_L, RIGHT_L, SQUARE, WASD, LIGHTNING_BOLT, RHODE_ISLAND};

//color for each different piece
struct rgb{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class PieceComponent {

public:
	//factory method
	//static Piece* makePiece(vector<Block>& blocks);
	virtual void rotate(coordinates pivot) = 0;
	virtual void traslate(PieceMovement direction) = 0;
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
	void traslate(PieceMovement direction);

	~Block() = default;
};



class Piece : public PieceComponent {
//Composite of blocks
protected:
	unique_ptr<Block> pivot;//smart pointer, self-manages freeing memory when out of scope
	vector<unique_ptr<Block>> blocks;
public:
	Piece() = default ;

	Piece(const Piece&) = delete;//no copy constructor or assignment
	Piece& operator= (const Piece&) = delete;

	Piece(Piece&&) = default;
	Piece& operator = (Piece&&) = default;

	~Piece() = default;

	void setPivot(coordinates pivot);
	void setBlocks(coordinates* blocks_coords, unsigned int length);
	coordinates getPivotCoords();

	void rotate(coordinates pivot);
	void traslate(PieceMovement direction);

    friend ostream& operator<<(ostream &out, const Piece& piece);
	friend class Board;
};

//builder pattern to create piece step by step depending on its type
class PieceBuilder{

public:
    PieceBuilder() = default ;
    virtual ~PieceBuilder() = default ;

    virtual void buildPivot() = 0 ;
    virtual void buildBlocks() = 0 ;

    void createPiece();

    Piece* getPieceMaker();

protected:
    unique_ptr<Piece> piece_maker ;
};


class StraightLineBuilder : public PieceBuilder {

protected:
    rgb color;
public:
    StraightLineBuilder() = default ;
    ~StraightLineBuilder() override = default ;

    void buildPivot();
    void buildBlocks();

} ;

