#ifndef CORNERGAME_STATE_H
#define CORNERGAME_STATE_H

#include <SDL_ttf.h>
#include "drawingHandler.h"
#include "entityBuilder.h"
#include "inputHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "soundHandler.h"

enum StateEnum {QUIT, START, PLAY, MENU, HIGHSCORE};

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
    virtual StateEnum run() = 0;
    virtual void cleanup() = 0;
};

class StartState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
public:
    StartState(int windowW, int windowH, std::list<Command*>& commandList,
               std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
               EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
               InputHandler& inputHandler, SoundHandler& soundHandler);
    ~StartState();
    void begin();
    StateEnum run();
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
    StateEnum run();
    void cleanup();
};


class HighscoreState : public State {
private:
    EntityBuilder& entityBuilder;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    SDL_Texture * texture;
    TTF_Font* font;
    SDL_Rect textRect;
public:
    HighscoreState(int windowW, int windowH, std::list<Command*>& commandList,
                   std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
                   EntityBuilder& entityBuilder, DrawingHandler& drawingHandler,
                   InputHandler& inputHandler, SoundHandler& soundHandler);
    ~HighscoreState();
    void begin();
    StateEnum run();
    void cleanup();
};

#endif
