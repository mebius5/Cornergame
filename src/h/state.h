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
    State ** state;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    std::list<Command*> * commandList;
    std::map<int, Entity*> * entityMap;
public:
    virtual ~State(){};
    int center(int large, int small);
    SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH);
    virtual void begin()=0;
    virtual void iterate(int dTime)=0;
    virtual void cleanup()=0;
};

class StartState : public State {
private:
    TTF_Font* font;
    DrawingHandler * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    SoundHandler * soundHandler;
    SDL_Rect textRect;
    int width;
    int height;

public:
    StartState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
    std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
    EntityBuilder * entityBuilder, InputHandler * inputHandler,
            SoundHandler * soundHandler);
    ~StartState();
    void begin();
    void iterate(int dTime);
    void cleanup();
};


class MenuState: public State {
private:
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    SoundHandler * soundHandler;
public:
    MenuState();
    ~MenuState();
};

class PlayState : public State {
private:
    //Private variables
    DrawingHandler  * drawer;
    EntityBuilder * entityBuilder;
    InputHandler * inputHandler;
    AiHandler * aiHandler;
    CollisionHandler * collisionHandler;
    SoundHandler * soundHandler;
    int windowW;
    int windowH;
    SDL_Rect backgroundRect;

public:
    //Public methods
    PlayState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
              std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
              EntityBuilder * entityBuilder, InputHandler * inputHandler,
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
    SoundHandler * soundHandler;
public:
    HighscoreState();
    ~HighscoreState();
};

#endif //CORNERGAME_STATE_H
