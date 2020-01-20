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
    gameGrid = new GameGrid();
    board = make_unique<Board>(window);
    createRandomPiece();

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
    moveTimer = SDL_AddTimer(500, addTimerCallback, nullptr);
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
    Command *command ;
    Piece *currentPiece ;
    int commandResult ;
    unsigned int counter = 0 ;
    while (SDL_PollEvent(&e) != 0)
    {
        counter++ ;
        handler.bindCommands();
        command = handler.handleInput(&e);
        //could be null command
        if (command){
            command->setGrid(gameGrid);//sets grid for check in execute
            //cout << *gameGrid << endl ;
            currentPiece = pieces.back().get();
            //cout << "Current Piece:" << endl << *currentPiece << endl ;
            commandResult = command->execute(currentPiece);

            if (commandResult == 0){
                //cout << "Undo last move" << endl;
                command->undo(currentPiece);
            }
            else if (commandResult == -1){
                //cout << "Creating new piece"<< endl ;
                SDL_RemoveTimer(moveTimer);
                command->undo(currentPiece);
                //cout << "Piece after undo for space: " << *currentPiece << flush ;
                gameGrid->setOccupiedBlocks(pieces.back().get());
                int rowFilled ;
                if ((rowFilled = gameGrid->isRowFilled()) != -1){
                    afterFilledRow(rowFilled);

                }

                createRandomPiece();
                break ;
                //moveTimer = SDL_AddTimer(500, addTimerCallback, nullptr);

            }
        }
        //render();
    }
    //delete command ;
}

GameGrid* Game::getGamegrid(){
    return this->gameGrid;
}

void Game::afterFilledRow(int rowFilled){

    //each block in that row becomes inactive
    //then each block above the row is traslated down
    for (auto it = begin(pieces); it != end(pieces); ++it){

        (*it)->blockIsOnFilledRow(rowFilled);
        (*it)->isOverFilledRow(rowFilled);
        if ((*it)->pieceHasToBeDeleted()){
            pieces.erase(it);
        }

    }
    //after messing up with pieces need to first reset then update bitset
    for (int i = Y_AXIS - 1; i > 0; i--){

        if (gameGrid->getGrid()[i].any()){
            gameGrid->getGrid()[i].reset();
        }
        else {
            break ;//because bitset starts being set from the bottom
        }

    }
    gameGrid->getGrid()[rowFilled].reset();
    for (auto &piece: pieces){
        gameGrid->setOccupiedBlocks(piece.get());
    }
}

void Game::render(){

    //Clear screen
    board->clearScreen();

    board->drawWalls();
    board->drawGridLines();
    board->highlightCurrentLines(pieces.back().get());
    //always draw last piece added
    for (auto &piece : pieces){
        board->drawPiece(piece.get());
    }


    board->renderPresent();
}

Game::~Game(){
    delete this->piece_builder;
    delete this->gameGrid;
    SDL_RemoveTimer(moveTimer);
}
