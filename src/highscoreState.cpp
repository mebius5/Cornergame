#include "state.h"

HighscoreState::HighscoreState(int windowW, int windowH, EntityManager& entMgr,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler) :
    State(entMgr, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    highscore(0) {
}

HighscoreState::~HighscoreState() {
}

void HighscoreState::begin() {
    this->soundHandler.playBackgroundMusic(MUSIC_HIGHSCORE);
    std::string hsText = "High Score:\n" + std::to_string(this->highscore);
    this->entityManager.createCenteredFadeInText(
                       "resources/CaesarDressing-Regular.ttf", hsText.c_str(),
                       100, 255, 255, 255, 0, this->windowW, this->windowH);
}

StateEnum HighscoreState::run() {
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

        if (timeElapsed > 5000){   //Return to MENU screen after 5 secs
            break;
        }
    }

    return STATE_MENU;
}

void HighscoreState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}

void HighscoreState::updateHighscores(Entity* hero) {
    if (hero->score->getScore() > this->highscore)
        this->highscore = hero->score->getScore();
}
