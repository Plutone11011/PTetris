#pragma once

#include "Piece.h"
//builder pattern to create piece step by step depending on its type
class PieceBuilder{

public:
    PieceBuilder() = default ;
    virtual ~PieceBuilder() = default ;

    void buildPivot();
    virtual void buildBlocks() = 0 ;
    virtual void buildColor() = 0 ;

    void createPiece();

    Piece* getPiece();

    //after all is done, has to move pointer to game and release it
    unique_ptr<Piece> getPieceMaker();

protected:
    unique_ptr<Piece> piece_maker ;
};

class StraightLineBuilder : public PieceBuilder {

public:
    StraightLineBuilder() = default ;

    ~StraightLineBuilder() override = default ;


    //void buildPivot();
    void buildBlocks();
    void buildColor();//cyan

} ;

class InverseLBuilder : public PieceBuilder{

public:
    InverseLBuilder() = default ;

    ~InverseLBuilder() override = default ;


    //void buildPivot();
    void buildBlocks();
    void buildColor();//blue

};

class RightLBuilder : public PieceBuilder{

public:
    RightLBuilder() = default ;
    ~RightLBuilder() override = default ;


    void buildBlocks();
    void buildColor();
};

class SquareBuilder : public PieceBuilder{
public:
    SquareBuilder() = default ;
    ~SquareBuilder() override = default ;


    void buildBlocks();
    void buildColor();
};

class RhodeIslandBuilder : public PieceBuilder{

public:
    RhodeIslandBuilder() = default ;
    ~RhodeIslandBuilder() override = default ;

    void buildBlocks();
    void buildColor();
};

class WasdBuilder :public PieceBuilder{
public:
    WasdBuilder() = default;
    ~WasdBuilder() override = default ;

    void buildBlocks();
    void buildColor();
};

class LightningBoltBuilder : public PieceBuilder{

public:
    LightningBoltBuilder() = default ;
    ~LightningBoltBuilder() override = default ;

    void buildBlocks();
    void buildColor();
};
