#include "EventHandler.h"

bool quit = false ;

void Command::setGrid(GameGrid *grid){
    this->gameGrid = grid ;
}
//execute commands return 1 if movement doesn't cause problems
//0 if it only needs an undo, -1 if it needs to stop the piece

//IACommand is automatic descent of piece, but also down key
int IACommand::execute(Piece *piece){
    piece->traslate(PieceMovement::DOWN);
    //short circuit
    if ((piece->isOnTheFloor()) || (gameGrid->isColliding(piece))){
        return -1 ;
    }
    else return 1 ;
}


void IACommand::undo(Piece *piece){
    piece->traslate(PieceMovement::UP);
}

int BackSpaceCommand::execute(Piece *piece){
    cout << "Piece before space: " << *piece << endl ;
    while (!((piece->isOnTheFloor()) || (gameGrid->isColliding(piece)))){
        piece->traslate(PieceMovement::DOWN);
    }
    cout << "Piece after space(no undo): " << *piece << endl ;
    return -1;
}

void BackSpaceCommand::undo(Piece *piece){
    //doesn't do anything
    piece->traslate(PieceMovement::UP);
}

int RotationCommand::execute(Piece *piece){
    piece->rotate(piece->getPivotCoords());
    if (gameGrid->isColliding(piece)){
        //colliding from the left means either the walls or another piece, either way undo
        return 0 ;
    }
    else return 1 ;
}

void RotationCommand::undo(Piece *piece){
    piece->inverserotate(piece->getPivotCoords());
}

int LeftCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::LEFT);
    if (gameGrid->isColliding(piece)){
        //colliding from the left means either the walls or another piece, either way undo
        return 0 ;
    }
    else return 1 ;
}

void LeftCommand::undo(Piece *piece){
    piece->traslate(PieceMovement::RIGHT);
}

int RightCommand::execute(Piece *piece){
    piece->traslate(PieceMovement::RIGHT);
    if (gameGrid->isColliding(piece)){
        //colliding from the left means either the walls or another piece, either way undo
        return 0 ;
    }
    else return 1 ;
}

void RightCommand::undo(Piece *piece){
    piece->traslate(PieceMovement::LEFT);
}

void EventHandler::bindCommands(){
    Key_up = new RotationCommand();
    Key_right = new RightCommand();
    Key_left = new LeftCommand();
    Key_down = new IACommand();
    Back_space = new BackSpaceCommand();
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
        case SDL_SCANCODE_SPACE:
            return Back_space;
        default:
            return nullptr ;

        }
    }
    else if (e->type == SDL_USEREVENT){
        return Key_down;
    }
    //cout << e->type << endl ;
    return nullptr ;//maybe deal with timer?
}

EventHandler::~EventHandler(){
    delete this->Key_down;
    delete this->Key_left;
    delete this->Key_right;
    delete this->Key_up;
}
