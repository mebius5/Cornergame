#include "state.h"

LevelSelectState::LevelSelectState(int windowW, int windowH, bool *levelSelected, EntityManager &entityManager,
                                   std::vector<Command *> &commandList, SDL_Renderer *renderer,
                                   DrawingHandler &drawingHandler, InputHandler &inputHandler,
                                   SoundHandler &soundHandler, ControlHandler &controlHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    levelSelected(levelSelected),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler) {
}

void LevelSelectState::begin(int /*level*/) {
    this->soundHandler.playBackgroundMusic(MUSIC_MENU);

    //this->entityManager.createLevelPreview(TEX_LEVEL1_PREVIEW, 250, 80);

    //this->entityManager.createLevelPreview(TEX_LEVEL2_PREVIEW, 250, 230);

    //this->entityManager.createLevelPreview(TEX_LEVEL3_PREVIEW, 250, 380);

    //this->entityManager.createLevelPreview(TEX_LEVEL4_PREVIEW, 250, 530);

    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, "SELECT LEVELS BELOW AND HIT PLAY",
            40, 255, 255, 255, 0, this->windowW, 50
    );

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Level 1", 20,
            255, 255, 255, 0, this->windowW, 100,
            0, 6, STATE_LEVEL_TRANSIT, this->levelSelected);

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Level 2", 20,
            255, 255, 255, 0, this->windowW, 200,
            1, 6, STATE_LEVEL_TRANSIT, this->levelSelected);

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Level 3", 20,
            255, 255, 255, 0, this->windowW, 300,
            2, 6, STATE_LEVEL_TRANSIT, this->levelSelected);

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Level 4", 20,
            255, 255, 255, 0, this->windowW, 400,
            3, 6, STATE_LEVEL_TRANSIT, this->levelSelected);

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Level 5", 20,
            255, 255, 255, 0, this->windowW, 500,
            4, 6, STATE_LEVEL_TRANSIT, this->levelSelected);

    this->entityManager.createHorizontallyCenteredSelectLevelText(
            FONT_GLOBAL, "Play", 30,
            255, 255, 255, 0, this->windowW, 600,
            5, 6, STATE_LEVEL_TRANSIT, this->levelSelected);
}

StateEnum LevelSelectState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int milliSecElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = (int) (currentTime - lastTime);
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

void LevelSelectState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}