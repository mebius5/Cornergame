#include "state.h"

MenuState::MenuState(int windowW, int windowH, std::list<Command*>& cmdList,
                     std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                     EntityBuilder& entBuilder, DrawingHandler& drawer,
                     InputHandler& inputHandler, SoundHandler& soundHandler) :
        State(cmdList, entMap, renderer, windowW, windowH),
        entityBuilder(entBuilder),
        drawingHandler(drawer),
        inputHandler(inputHandler),
        soundHandler(soundHandler) {
}

MenuState::~MenuState() {
}

void MenuState::begin() {
    // play background music
    this->soundHandler.playBackgroundMusic("music/a_winter_kiss_menu.xm");

    Entity * playText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Play",
            100,
            255, 255, 255, 0, this->windowW, 100);
    entityMap.operator[](playText->getId())= playText;

    Entity * highText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Highscore",
            100,
            255, 255, 255, 0, this->windowW, 300);
    entityMap.operator[](highText->getId())= highText;

    Entity * quitText = entityBuilder.createHorizontallyCenteredFadeInText(
            "resources/CaesarDressing-Regular.ttf", "Quit",
            100,
            255, 255, 255, 0, this->windowW, 500);
    entityMap.operator[](quitText->getId())= quitText;
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
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return QUIT;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    return QUIT;
                } else
                    this->inputHandler.handleEvent(event);
            } else {
                this->inputHandler.handleEvent(event);
            }
        }

        this->inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);

        SDL_RenderClear(this->renderer);

        this->drawingHandler.draw(dt);

        SDL_RenderPresent(this->renderer);

        if(milliSecElapsed>=10000){ //Return menu after 10000
            break;
        }
    }
    return PLAY;
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
