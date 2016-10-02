#ifndef CORNERGAME_STATE_H
#define CORNERGAME_STATE_H

#include <SDL_ttf.h>
#include "drawingHandler.h"
#include "entityBuilder.h"
#include "inputHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "soundHandler.h"
#include "controlHandler.h"

class State {
protected:
    int windowW;
    int windowH;
    std::list<Command*>& commandList;
    std::map<int, Entity*>& entityMap;
    SDL_Renderer* renderer;
public:
    enum StateEnum {NONE, QUIT, START, PLAY, MENU, HIGHSCORE};

    State(std::list<Command*>& commandList, std::map<int, Entity*>& entityMap,
          SDL_Renderer* renderer, int windowW, int windowH);
    virtual ~State() { };
    int center(int large, int small);
    SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH);
    virtual void begin() = 0;
    virtual State::StateEnum run() = 0;
    virtual void cleanup() = 0;
};

class StartState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
public:
    StartState(int windowW, int windowH, std::list<Command*>& commandList,
               std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
               EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
               InputHandler& inputHandler, SoundHandler& soundHandler,
               ControlHandler& controlHandler);
    ~StartState();
    void begin();
    State::StateEnum run();
    void cleanup();
};


class MenuState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
public:
    MenuState(int windowW, int windowH, std::list<Command*>& commandList,
               std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
               EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
               InputHandler& inputHandler, SoundHandler& soundHandler,
               ControlHandler& controlHandler);
    ~MenuState();
    void begin();
    State::StateEnum run();
    void cleanup();
};

class PlayState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    AiHandler& aiHandler;
    CollisionHandler& collisionHandler;
    ControlHandler& controlHandler;
public:
    PlayState(int windowW, int windowH, std::list<Command*>& cmdList,
              std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
              EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
              InputHandler& inputHandler, SoundHandler& soundHandler,
              AiHandler& aiHandler, CollisionHandler& collisionHandler,
              ControlHandler& controlHandler);
    ~PlayState();
    void begin();
    State::StateEnum run();
    void cleanup();
};


class HighscoreState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
public:
    HighscoreState(int windowW, int windowH, std::list<Command*>& commandList,
                   std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
                   EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
                   InputHandler& inputHandler, SoundHandler& soundHandler,
                   ControlHandler& controlHandler);
    ~HighscoreState();
    void begin();
    State::StateEnum run();
    void cleanup();
};

#endif
