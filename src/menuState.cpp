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

void MenuState::begin(int) {
    this->soundHandler.playBackgroundMusic(MUSIC_MENU);

    this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Play", 80,
            255, 255, 255, 0, this->windowW, 100,
            0, 5, STATE_LEVEL_TRANSIT);

    this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Tutorial", 80,
            255, 255, 255, 0, this->windowW, 200,
            1, 5, STATE_TUTORIAL);

    this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Adjust Audio Volume", 80,
            255, 255, 255, 0, this->windowW, 300,
            2, 5, STATE_NONE);

    this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Highscore", 80,
            255, 255, 255, 0, this->windowW, 400,
            3, 5, STATE_HIGHSCORE);

    this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Quit", 80,
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

        this->inputHandler.handleEvents(dt);
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
