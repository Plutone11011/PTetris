#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <ostream>
#include <iostream>

#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20
#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1280
#define LEFT_WALL_X 200
#define WALL_WIDTH 30
#define WALL_HEIGTH SCREEN_HEIGHT
#define BOARD_WIDTH 820
#define BOARD_HEIGHT WALL_HEIGTH
#define RIGHT_WALL_X (SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH)
#define X_AXIS (BOARD_WIDTH / BLOCK_WIDTH)
#define Y_AXIS (WALL_HEIGTH / BLOCK_HEIGHT)

using namespace std;

struct coordinates {

	int x;
	int y;

};

enum class PieceMovement { LEFT, RIGHT, DOWN, UP };
//enum class PieceTypes {STRAIGHT_LINE, INVERSE_L, RIGHT_L, SQUARE, WASD, LIGHTNING_BOLT, RHODE_ISLAND};

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
	virtual void inverserotate(coordinates pivot) = 0;
};

//single block with coordinates
class Block : public PieceComponent {

private:
	coordinates block_coords;
	bool active ; //tells if it's still part of the board

public:
	Block() = default;
	Block(coordinates block_coords);

	coordinates getCoords();
	void setCoords(coordinates);

	void setActive(bool active);
	bool getActive();
	//default copy and assignment constructors
	void rotate(coordinates pivot);
	void inverserotate(coordinates pivot);
	void traslate(PieceMovement direction);

	~Block() = default;
};



class Piece : public PieceComponent {
//Composite of blocks
protected:
	unique_ptr<Block> pivot;//smart pointer, self-manages freeing memory when out of scope
	vector<unique_ptr<Block>> blocks;
	rgb color;
public:
	Piece() = default ;

	Piece(const Piece&) = delete;//no copy constructor or assignment
	Piece& operator= (const Piece&) = delete;

	Piece(Piece&&) = default;
	Piece& operator = (Piece&&) = default;

	~Piece() = default;

    //methods called by builder to allocate memory and instantiate it with parameter
	void setPivot(coordinates pivot);
	void setBlocks(vector<coordinates> blocks_coords);
	void setColor(const rgb& color);

	coordinates getPivotCoords();
    rgb* getColor();

	void rotate(coordinates pivot);
	void inverserotate(coordinates pivot);//undo rotation with counterclockwise matrix
	void traslate(PieceMovement direction);

	bool isOnTheFloor();//checks if piece is clashing with the floor
    void isOverFilledRow(int row);//utility methods for line completion in tetris game
    void blockIsOnFilledRow(int row);
    bool pieceHasToBeDeleted();

    friend ostream& operator<<(ostream &out, const Piece& piece);
	friend class Board;
	friend class GameGrid ;
};



