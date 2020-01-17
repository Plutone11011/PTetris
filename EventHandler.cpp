#include "EventHandler.h"

bool quit = false ;

//IACommand is automatic descent of piece, but also down key
void IACommand::execute(Piece *piece){
    piece->traslate(PieceMovement::DOWN);
}

void IACommand::undo(Piece *piece){
    piece->traslate(PieceMovement::UP);
}

void RotationCommand::execute(Piece *piece){
    piece->rotate(piece->getPivotCoords());
}

void RotationCommand::undo(Piece *piece){
    piece->inverserotate(piece->getPivotCoords());
}

void LeftCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::LEFT);
}

void LeftCommand::undo(Piece *piece){
    piece->traslate(PieceMovement::RIGHT);
}

void RightCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::RIGHT);
}

void RightCommand::undo(Piece *piece){
    piece->traslate(PieceMovement::LEFT);
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

