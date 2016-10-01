#ifndef CORNERGAME_STATE_H
#define CORNERGAME_STATE_H

#include <SDL_ttf.h>
#include "drawingHandler.h"
#include "entityBuilder.h"
#include "inputHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "soundHandler.h"

class State {
protected:
    int windowW;
    int windowH;
    std::list<Command*>& commandList;
    std::map<int, Entity*>& entityMap;
    SDL_Renderer* renderer;
public:
    State(std::list<Command*>& commandList, std::map<int, Entity*>& entityMap,
          SDL_Renderer* renderer, int windowW, int windowH);
    virtual ~State() { };
    int center(int large, int small);
    SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH);
    virtual void begin() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;
};

class StartState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    SDL_Texture * texture;
    TTF_Font* font;
    SDL_Rect textRect;

public:
    StartState(int windowW, int windowH, std::list<Command*>& commandList,
               std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
               EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
               InputHandler& inputHandler, SoundHandler& soundHandler);
    ~StartState();
    void begin();
    void run();
    void cleanup();
};


class MenuState: public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
public:
    MenuState();
    ~MenuState();
};

class PlayState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    AiHandler& aiHandler;
    CollisionHandler& collisionHandler;

public:
    PlayState(int windowW, int windowH, std::list<Command*>& cmdList,
              std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
              EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
              InputHandler& inputHandler, SoundHandler& soundHandler,
              AiHandler& aiHandler, CollisionHandler& collisionHandler);
    ~PlayState();
    void begin();
    void run();
    void cleanup();
};


class HighscoreState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
public:
    HighscoreState();
    ~HighscoreState();
};

#endif
