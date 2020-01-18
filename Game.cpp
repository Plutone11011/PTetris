#include "Game.h"
#include <ctime>

uint32_t addTimerCallback(uint32_t interval, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    //no function or parameters to pass to the main thread
    userevent.data1 = nullptr;
    userevent.data2 = nullptr;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);

}

Game::Game(SDL_Window* window){
    piece_builder = nullptr;
    gameGrid = make_unique<GameGrid>();
    board = make_unique<Board>(window);
    createRandomPiece();
    moveTimer = SDL_AddTimer(500, addTimerCallback, nullptr);
}

void Game::createRandomPiece(){
    srand(time(nullptr));
    switch(rand() % 7){
        case 0:
        {
            //Straight line
            StraightLineBuilder sb;
            makePiece(&sb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(sb.getPieceMaker());
            break ;
        }
        case 1:
        {
            InverseLBuilder ib;
            makePiece(&ib);
            //move piece ownership from piecebuilder to game
            pieces.push_back(ib.getPieceMaker());
            break ;
        }
        case 2:
        {
            RightLBuilder rb;
            makePiece(&rb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(rb.getPieceMaker());
            break ;
        }
        case 3:
        {
            SquareBuilder sqb;
            makePiece(&sqb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(sqb.getPieceMaker());
            break ;
        }
        case 4:
        {
            RhodeIslandBuilder rhb;
            makePiece(&rhb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(rhb.getPieceMaker());
            break ;
        }
        case 5:
        {
            LightningBoltBuilder lb;
            makePiece(&lb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(lb.getPieceMaker());
            break ;
        }
        case 6:
        {
            WasdBuilder wb;
            makePiece(&wb);
            //move piece ownership from piecebuilder to game
            pieces.push_back(wb.getPieceMaker());
            break ;
        }
        default:
            break ;
    }
}



//builds piece of the type istantiated by the builder
void Game::makePiece(PieceBuilder* piece_builder){

    this->piece_builder = piece_builder;

    this->piece_builder->createPiece();
    this->piece_builder->buildPivot();
    this->piece_builder->buildBlocks();
    this->piece_builder->buildColor();


}

void Game::eventLoop(){
    int isColliding;
    Command *command ;
    Piece *currentPiece ;
    while (SDL_PollEvent(&e) != 0)
    {
        handler.bindCommands();
        command = handler.handleInput(&e);
        //could be null command
        if (command){
            currentPiece = pieces.back().get();
            command->execute(currentPiece);

            isColliding = gameGrid->isColliding(currentPiece);
            if (isColliding){
                command->undo(currentPiece);
            }
        }
    }
}

void Game::render(){

    //Clear screen
    board->clearScreen();

    board->drawWalls();
    //always draw last piece added
    board->drawPiece(pieces.back().get());

    board->renderPresent();
}
