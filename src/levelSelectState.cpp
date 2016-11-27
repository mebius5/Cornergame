#include "state.h"

LevelSelectState::LevelSelectState(int windowW, int windowH, EntityManager& entityManager,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler) {
}

void LevelSelectState::begin(int /*level*/) {
    this->soundHandler.playBackgroundMusic(MUSIC_MENU);

    this->entityManager.createLevelPreview(TEX_LEVEL1_PREVIEW, 250, 80);

    this->entityManager.createLevelPreview(TEX_LEVEL2_PREVIEW, 250, 230);

    this->entityManager.createLevelPreview(TEX_LEVEL3_PREVIEW, 250, 380);

    this->entityManager.createLevelPreview(TEX_LEVEL4_PREVIEW, 250, 530);

    level1 = this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Level 1", 20,
            255, 255, 255, 0, this->windowW, 50,
            0, 5, STATE_LEVEL_TRANSIT);

    level2 = this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Level 2", 20,
            255, 255, 255, 0, this->windowW, 200,
            1, 5, STATE_LEVEL_TRANSIT);

    level3 = this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Level 3", 20,
            255, 255, 255, 0, this->windowW, 350,
            2, 5, STATE_LEVEL_TRANSIT);

    level4 = this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Level 4", 20,
            255, 255, 255, 0, this->windowW, 500,
            3, 5, STATE_LEVEL_TRANSIT);
    level5 = this->entityManager.createHorizontallyCenteredFadeInMenuText(
            FONT_GLOBAL, "Level 5", 20,
            255, 255, 255, 0, this->windowW, 650,
            4, 5, STATE_LEVEL_TRANSIT);
}

int LevelSelectState::nextLevel() {
    if (dynamic_cast<MenuOptionInputComponent*>(level1->input)->isSelected()) {
        return 1;
    }
    if (dynamic_cast<MenuOptionInputComponent*>(level2->input)->isSelected()) {
        return 2;
    }
    if (dynamic_cast<MenuOptionInputComponent*>(level3->input)->isSelected()) {
        return 3;
    }
    if (dynamic_cast<MenuOptionInputComponent*>(level4->input)->isSelected()) {
        return 4;
    }
    if (dynamic_cast<MenuOptionInputComponent*>(level5->input)->isSelected()) {
        return 5;
    }
    else return 1;
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