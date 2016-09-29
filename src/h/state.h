

#ifndef CORNERGAME_STATE_H
#define CORNERGAME_STATE_H

#include "drawingHandler.h"
#include "entityBuilder.h"
#include "inputHandler.h"
#include "aiHandler.h"
#include "locationHandler.h"
#include "collisionHandler.h"
#include "soundHandler.h"

class State {
protected:
    SDL_Texture * texture;
    SDL_Renderer * renderer;
    std::map<int, Entity*> * entityMap;
    std::list<Command*> * commandList;
public:
    virtual ~State(){};
    virtual void begin()=0;
    virtual void iterate(int dTime)=0;
    virtual void cleanup()=0;
};

class StartState : public State {
private:
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    LocationHandler * locationHandler;
    SoundHandler * soundHandler;
public:
    StartState();
    ~StartState();
};


class MenuState: public State {
private:
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    LocationHandler * locationHandler;
    SoundHandler * soundHandler;
public:
    MenuState();
    ~MenuState();
};

class PlayState : public State {
private:
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    LocationHandler * locationHandler;
    AiHandler * aiHandler;
    CollisionHandler * collisionHandler;
    SoundHandler * soundHandler;
    int windowW;
    int windowH;
    SDL_Rect backgroundRect;

public:
    PlayState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
              std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
              EntityBuilder * entityBuilder, InputHandler * inputHandler, LocationHandler * locationHandler,
              AiHandler * aiHandler, CollisionHandler * collisionHandler, SoundHandler * soundHandler);

    ~PlayState();
    void begin();
    void iterate(int dTime);
    void cleanup();
};


class HighscoreState : public State {
private:
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    LocationHandler * locationHandler;
    SoundHandler * soundHandler;
public:
    HighscoreState();
    ~HighscoreState();
};

#endif //CORNERGAME_STATE_H
