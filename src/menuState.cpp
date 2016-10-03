#include "state.h"

MenuState::MenuState(int windowW, int windowH, std::list<Command*>& cmdList,
                     std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                     EntityBuilder& entBuilder, DrawingHandler& drawer,
                     InputHandler& inputHandler, SoundHandler& soundHandler,
                     ControlHandler& controlHandler) :
    State(cmdList, entMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawer),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler) {
}

MenuState::~MenuState() {
}

void MenuState::begin() {
    this->soundHandler.playBackgroundMusic("music/a_winter_kiss_menu.xm");

    Entity * playText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Play",
            80,
            255, 255, 255, 0, this->windowW, 100,
            0, 5, STATE_PLAY);
    this->entityMap[playText->getId()] = playText;

    Entity * brightText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Adjust Visual Brightness",
            80,
            255, 255, 255, 0, this->windowW, 200,
            1, 5, STATE_NONE);
    this->entityMap[brightText->getId()] = brightText;

    Entity * audioText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Adjust Audio Volume",
            80,
            255, 255, 255, 0, this->windowW, 300,
            2, 5, STATE_NONE);
    this->entityMap[audioText->getId()] = audioText;

    Entity * scoreText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Highscore",
            80,
            255, 255, 255, 0, this->windowW, 400,
            3, 5, STATE_HIGHSCORE);
    this->entityMap[scoreText->getId()] = scoreText;

    Entity * quitText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Quit",
            80,
            255, 255, 255, 0, this->windowW, 500,
            4, 5, STATE_QUIT);
    this->entityMap[quitText->getId()] = quitText;
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
        //inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE && nextState != STATE_MENU)
            return nextState;
    }

    return STATE_NONE;      // NOT REACHED
}

void MenuState::cleanup() {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entities from map
    }
    entityMap.clear();
    commandList.clear();

   this->soundHandler.stopBackgroundMusic();
}
