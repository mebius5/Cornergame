#ifndef CORNERGAME_STATE_H
#define CORNERGAME_STATE_H

#include <SDL_ttf.h>
#include "drawingHandler.h"
#include "entityManager.h"
#include "inputHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "soundHandler.h"
#include "controlHandler.h"
#include "enums.h"
#include "scoreHandler.h"
#include "level.h"

class State {
protected:
    int windowW;
    int windowH;
    EntityManager& entityManager;
    std::vector<Command*>& commandList;
    SDL_Renderer* renderer;
public:
    State(EntityManager& entityManager, std::vector<Command*>& commandList,
          SDL_Renderer* renderer, int windowW, int windowH);
    virtual ~State() { };
    static int center(int large, int small);
    static SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH);
    virtual void begin() = 0;
    virtual StateEnum run() = 0;
    virtual void cleanup(StateEnum nextState) = 0;
};

class StartState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    CollisionHandler& collisionHandler;
public:
    StartState(int windowW, int windowH, EntityManager& entityManager,
               std::vector<Command*>& commandList, SDL_Renderer* renderer,
               DrawingHandler& drawingHandler, InputHandler& inputHandler,
               SoundHandler& soundHandler, ControlHandler& controlHandler,
               CollisionHandler& collisionHandler);
    ~StartState();
    void begin();
    StateEnum run();
    void cleanup(StateEnum next);
};


class MenuState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
public:
    MenuState(int windowW, int windowH, EntityManager& entityManager,
              std::vector<Command*>& commandList, SDL_Renderer* renderer,
              DrawingHandler& drawingHandler, InputHandler& inputHandler,
              SoundHandler& soundHandler, ControlHandler& controlHandler);
    ~MenuState();
    void begin();
    StateEnum run();
    void cleanup(StateEnum next);
};

class HighscoreState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    int highscore;
public:
    HighscoreState(int windowW, int windowH, EntityManager& entityManager,
                   std::vector<Command*>& commandList, SDL_Renderer* renderer,
                   DrawingHandler& drawingHandler, InputHandler& inputHandler,
                   SoundHandler& soundHandler, ControlHandler& controlHandler);
    ~HighscoreState();
    void begin();
    StateEnum run();
    void cleanup(StateEnum next);
    void updateHighscores(Entity* hero);
};

class ResultsState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    int score;
    bool victory;
public:
    ResultsState(int windowW, int windowH, EntityManager& entityManager,
                   std::vector<Command*>& commandList, SDL_Renderer* renderer,
                   DrawingHandler& drawingHandler, InputHandler& inputHandler,
                   SoundHandler& soundHandler, ControlHandler& controlHandler);
    ~ResultsState();
    void begin();
    StateEnum run();
    void cleanup(StateEnum next);
    void updateResults(Entity* hero);
};

class PlayState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    AiHandler& aiHandler;
    CollisionHandler& collisionHandler;
    ScoreHandler& scoreHandler;
    ResultsState& resultsState;
    HighscoreState& highscoreState;
    Entity* hero;
public:
    PlayState(int windowW, int windowH, EntityManager& entityManager,
              std::vector<Command*>& commandList, SDL_Renderer* renderer,
              DrawingHandler& drawingHandler, InputHandler& inputHandler,
              SoundHandler& soundHandler, ControlHandler& controlHandler,
              AiHandler& aiHandler, CollisionHandler& collisionHandler, ScoreHandler& scoreHandler,
              ResultsState& resultsState, HighscoreState& highscoreState);
    ~PlayState();
    void begin();
    StateEnum run();
    void cleanup(StateEnum next);
};

#endif
