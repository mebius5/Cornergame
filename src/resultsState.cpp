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
    score(0) {
}

ResultsState::~ResultsState() {
}

void ResultsState::begin(int) {
    this->soundHandler.playBackgroundMusic(MUSIC_HIGHSCORE);

    std::string resultString;
    if (this->victory)
        resultString = "Victory! Score: " + std::to_string(this->score);
    else
        resultString = "Defeat! Score: " + std::to_string(this->score);

    this->entityManager.createCenteredFadeInText(
                   "resources/CaesarDressing-Regular.ttf", resultString.c_str(),
                   100, 255, 255, 255, 0, this->windowW, this->windowH);
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
        this->inputHandler.update(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState)
            return nextState;

        if (timeElapsed > 5000) {   //Return to MENU screen after 5 secs
            break;
        }
    }

    return STATE_MENU;
}

void ResultsState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}

void ResultsState::updateResults(Entity* hero) {
    if (hero->health->getHealth() <= 0)
        this->victory = false;
    else
        this->victory = true;
    this->score = hero->score->getScore();
}
