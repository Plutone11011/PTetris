#pragma once
#include <SDL2/SDL_events.h>
#include "Piece.h"
//implement input handling with command pattern
extern bool quit ;

class Command{
public:
    Command()=default;
    virtual ~Command() {}
    virtual void execute(Piece *piece) = 0;
};

class IACommand : public Command{
public:
    void execute(Piece *piece) override;
};

class RotationCommand : public Command{
public:
    void execute(Piece *piece) override;
};

class LeftCommand : public Command{
public:
    void execute(Piece *piece) override;
};

class RightCommand : public Command{
public:
    void execute(Piece *piece) override;
};

class EventHandler {

private:
    Command* Key_up;
    Command* Key_right;
    Command* Key_left;
    Command* Key_down;
public:
    EventHandler()=default;
    ~EventHandler()=default;

    //now making static binding
    //but it should be configurable by user
    void bindCommands();
    void unbindCommands();
    Command* handleInput(SDL_Event *e);
};
