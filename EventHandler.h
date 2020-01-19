#pragma once
#include <SDL2/SDL_events.h>
#include "Piece.h"
#include "Board.h"
//implement input handling with command pattern
extern bool quit ;

class Command{
protected:
    GameGrid* gameGrid;
public:
    Command()=default;
    virtual ~Command() {}
    virtual int execute(Piece *piece) = 0;
    virtual void undo(Piece *piece) = 0 ;//each undo is contrary operation to execute
    void setGrid(GameGrid *gameGrid);
};

class BackSpaceCommand : public Command{
public:
        int execute(Piece *piece) override;
        void undo(Piece *piece) override ;
};

class IACommand : public Command{
public:
    int execute(Piece *piece) override;
    void undo(Piece *piece) override ;
};

class RotationCommand : public Command{
public:
    int execute(Piece *piece) override;
    void undo(Piece *piece) override ;
};

class LeftCommand : public Command{
public:
    int execute(Piece *piece) override;
    void undo(Piece *piece) override ;
};

class RightCommand : public Command{
public:
    int execute(Piece *piece) override;
    void undo(Piece *piece) override ;
};

class EventHandler {

private:
    Command* Key_up;
    Command* Key_right;
    Command* Key_left;
    Command* Key_down;
    Command* Back_space;
public:
    EventHandler()=default;
    ~EventHandler();

    //now making static binding
    //but it should be configurable by user
    void bindCommands();
    Command* handleInput(SDL_Event *e);
};


