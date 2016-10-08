#include "state.h"

MenuState::MenuState(int windowW, int windowH, EntityManager& entityManager,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler) {
}

MenuState::~MenuState() {
}

void MenuState::begin() {
    this->soundHandler.playBackgroundMusic(MUSIC_MENU);

    this->entityManager.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Play",
            80,
            255, 255, 255, 0, this->windowW, 100,
            0, 5, STATE_PLAY);

    this->entityManager.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Adjust Visual Brightness",
            80,
            255, 255, 255, 0, this->windowW, 200,
            1, 5, STATE_NONE);

    this->entityManager.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Adjust Audio Volume",
            80,
            255, 255, 255, 0, this->windowW, 300,
            2, 5, STATE_NONE);

    this->entityManager.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Highscore",
            80,
            255, 255, 255, 0, this->windowW, 400,
            3, 5, STATE_HIGHSCORE);

    this->entityManager.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Quit",
            80,
            255, 255, 255, 0, this->windowW, 500,
            4, 5, STATE_QUIT);
}

StateEnum MenuState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int milliSecElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        milliSecElapsed += dt;

        this->inputHandler.handleEvents();
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE && nextState != STATE_MENU)
            return nextState;
    }

    return STATE_NONE;      // NOT REACHED
}

void MenuState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}
