#include "state.h"

ResultsState::ResultsState(int windowW, int windowH, EntityManager& entMgr,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler) :
    State(entMgr, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    score(0),
    hero1Victory(true)
{
}

ResultsState::~ResultsState() {
}

void ResultsState::begin(int) {
    this->soundHandler.playBackgroundMusic(MUSIC_HIGHSCORE);

    std::string victoryString;
    std::string scoreString;
    if (this->hero1Victory){
        victoryString = "Player 1 Wins!";
        scoreString = "Score: " + std::to_string(this->score);
    }
    else{
        victoryString = "Player 2 Wins!";
        scoreString = "Score: " + std::to_string(this->score);
    }

    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, victoryString.c_str(),
            100, 255, 255, 255, 0, this->windowW, 200
    );

    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, scoreString.c_str(),
            100, 255, 255, 255, 0, this->windowW, 400
    );
}

StateEnum ResultsState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int timeElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        timeElapsed+=dt;

        this->inputHandler.handleEvents();
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            return nextState;

        if (timeElapsed > 5000) {   //Return to MENU screen after 5 secs
            break;
        }
    }

    return STATE_PLAY;
}

void ResultsState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}

void ResultsState::updateResults(Entity *hero1, Entity *hero2) {
    if (hero2->health->getHealth() <= 0){
        this->hero1Victory = true;
        this->score = hero1->score->getScore();
    }
    else{
        this->hero1Victory = false;
        this->score = hero2->score->getScore();
    }
}
