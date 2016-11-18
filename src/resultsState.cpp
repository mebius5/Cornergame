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
    hero1Victory(true) {
}

void ResultsState::setVictorious(Entity* winner, Entity* loser) {
    winner->drawX -= winner->drawWidth;
    winner->drawY -= winner->drawHeight;
    winner->drawHeight *= 3;
    winner->drawWidth *= 3;
    winner->actionState = ACTION_JUMP;
    loser->actionState = ACTION_IDLE;
    winner->score->wins++;
}

void ResultsState::begin(int /*level*/) {
    this->soundHandler.playBackgroundMusic(MUSIC_HIGHSCORE);
    this->drawingHandler.initializeCamera(1024, 704, true);

    // Update entities based on PlayState results
    this->entityManager.addEntity(this->hero1);
    this->entityManager.addEntity(this->hero2);
    DynamicCollisionComponent* comp1 = static_cast<DynamicCollisionComponent*>(this->hero1->collision);
    comp1->onGround = false;
    comp1->onLeftWall = false;
    comp1->onRightWall = false;
    this->hero1->dir = 1;
    this->hero1->x = 400;
    this->hero1->y = 120;
    this->hero1->physics->xVelocity = 0.0f;
    this->hero1->physics->yVelocity = 0.0f;

    DynamicCollisionComponent* comp2 = static_cast<DynamicCollisionComponent*>(this->hero2->collision);
    comp2->onGround = false;
    comp2->onLeftWall = false;
    comp2->onRightWall = false;
    this->hero2->dir = -1;
    this->hero2->x = 624;
    this->hero2->y = 120;
    this->hero2->physics->xVelocity = 0.0f;
    this->hero2->physics->yVelocity = 0.0f;

    std::string victoryString;
    std::string scoreString;
    if (this->hero1Victory)
        victoryString = "Player 1 Wins!";
    else
        victoryString = "Player 2 Wins!";
    scoreString = "Record: " + std::to_string(this->hero1->score->wins)
                  + " - " + std::to_string(this->hero2->score->wins);
    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, victoryString.c_str(),
            100, 255, 255, 255, 0, this->windowW, 300);
    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, scoreString.c_str(),
            100, 255, 255, 255, 0, this->windowW, 500);
}

StateEnum ResultsState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int timeElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        timeElapsed += dt;

        this->inputHandler.handleEvents(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            return nextState;

        if (this->controlHandler.isPreviewOff())    // user pressed 'P'
            break;
        if (timeElapsed > 5000)      // return to MENU screen after 5 secs
            break;
    }

    return STATE_LEVEL_TRANSIT;
}

void ResultsState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}

void ResultsState::updateResults(Entity* hero1, Entity* hero2) {
    this->hero1 = hero1;     // save heroes to place in EntityMap during begin()
    this->hero2 = hero2;
    hero1->art->validate();
    hero2->art->validate();
    this->hero1Victory = (hero2->health->getHealth() <= 0);
    if (this->hero1Victory)
        this->setVictorious(this->hero1, this->hero2);
    else
        this->setVictorious(this->hero2, this->hero1);
}
