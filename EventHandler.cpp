#include "EventHandler.h"

bool quit = false ;


void IACommand::execute(Piece *piece){
    piece->traslate(PieceMovement::DOWN);
}

void RotationCommand::execute(Piece *piece){
    piece->rotate(piece->getPivotCoords());
}

void LeftCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::LEFT);
}

void RightCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::RIGHT);
}

void EventHandler::bindCommands(){
    Key_up = new RotationCommand();
    Key_right = new RightCommand();
    Key_left = new LeftCommand();
    Key_down = new IACommand();
}

Command* EventHandler::handleInput(SDL_Event *e){

    if(e->type == SDL_QUIT){
        quit = true;
        return nullptr;
    }
    else if (e->type == SDL_KEYDOWN){
        switch(e->key.keysym.scancode){

        case SDL_SCANCODE_UP:
            return Key_up ;
        case SDL_SCANCODE_RIGHT:
            return Key_right ;
        case SDL_SCANCODE_LEFT:
            return Key_left;
        case SDL_SCANCODE_DOWN:
            return Key_down;
        default:
            return nullptr ;

        }
    }
    else if (e->type == SDL_USEREVENT){
        return Key_down;
    }
    return nullptr ;//maybe deal with timer?
}

void EventHandler::unbindCommands(){
    delete Key_up;
    delete Key_right;
    delete Key_left;
    delete Key_down;
}
