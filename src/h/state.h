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
#include "consts.h"
#include "scoreHandler.h"
#include "physicsHandler.h"
#include "level.h"
#include "powerUpHandler.h"
#include "timeHandler.h"

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
    static int center(int large, int small);
    static SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH);
    virtual void begin(int level) = 0;
    virtual StateEnum run() = 0;
    virtual void cleanup(StateEnum nextState) = 0;
    virtual int nextLevel() = 0;
};

class StartState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    CollisionHandler& collisionHandler;
    PhysicsHandler& physicsHandler;
public:
    StartState(int windowW, int windowH, EntityManager& entityManager,
               std::vector<Command*>& commandList, SDL_Renderer* renderer,
               DrawingHandler& drawingHandler, InputHandler& inputHandler,
               SoundHandler& soundHandler, ControlHandler& controlHandler,
               CollisionHandler& collisionHandler, PhysicsHandler& physicsHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    int nextLevel();
};

class LevelSelectState : public State {
private: 
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    Entity* level1;
    Entity* level2;
    Entity* level3;
    Entity* level4;
    Entity* level5;
public:
    LevelSelectState(int windowW, int windowH, EntityManager& entityManager,
              std::vector<Command*>& commandList, SDL_Renderer* renderer,
              DrawingHandler& drawingHandler, InputHandler& inputHandler,
              SoundHandler& soundHandler, ControlHandler& controlHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    int nextLevel();
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
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    int nextLevel();
};

class HighscoreState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    int p1wins;
    int p2wins;
public:
    HighscoreState(int windowW, int windowH, EntityManager& entityManager,
                   std::vector<Command*>& commandList, SDL_Renderer* renderer,
                   DrawingHandler& drawingHandler, InputHandler& inputHandler,
                   SoundHandler& soundHandler, ControlHandler& controlHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    void updateHighscores(Entity* hero1, Entity* hero2);
    int nextLevel();
};

class ResultsState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    bool hero1Victory;
    Entity* hero1;
    Entity* hero2;
    void setVictorious(Entity* winner, Entity* loser);
public:
    ResultsState(int windowW, int windowH, EntityManager& entityManager,
                   std::vector<Command*>& commandList, SDL_Renderer* renderer,
                   DrawingHandler& drawingHandler, InputHandler& inputHandler,
                   SoundHandler& soundHandler, ControlHandler& controlHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    void updateResults(Entity* hero1, Entity* hero2);
    int nextLevel();
};

class LevelTransitState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    std::string transitionText;
public:
    LevelTransitState(int windowW, int windowH, EntityManager& entityManager,
                 std::vector<Command*>& commandList, SDL_Renderer* renderer,
                 DrawingHandler& drawingHandler, InputHandler& inputHandler,
                 SoundHandler& soundHandler, ControlHandler& controlHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    void readTransitString(int level);
    int nextLevel();
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
    PhysicsHandler& physicsHandler;
    PowerUpHandler& powerUpHandler;
    TimeHandler& timeHandler;
    ResultsState& resultsState;
    HighscoreState& highscoreState;
    Entity* hero1;
    Entity* hero2;
    int levelW;
    int levelH;
    int p1wins;
    int p2wins;
public:
    PlayState(int windowW, int windowH, EntityManager& entityManager,
              std::vector<Command*>& commandList, SDL_Renderer* renderer,
              DrawingHandler& drawingHandler, InputHandler& inputHandler,
              SoundHandler& soundHandler, ControlHandler& controlHandler,
              AiHandler& aiHandler, CollisionHandler& collisionHandler,
              ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler,
              PowerUpHandler& powerUpHandler, TimeHandler& timeHandler,
              ResultsState& resultsState, HighscoreState& highscoreState);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    int nextLevel();
};

class TutorialState : public State {
private:
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
    AiHandler& aiHandler;
    CollisionHandler& collisionHandler;
    ScoreHandler& scoreHandler;
    PhysicsHandler& physicsHandler;
    PowerUpHandler& powerUpHandler;
    TimeHandler& timeHandler;
    Entity* hero;
    Entity* hero2;
    int levelW;
    int levelH;
public:
    TutorialState(int windowW, int windowH, EntityManager& entityManager,
              std::vector<Command*>& commandList, SDL_Renderer* renderer,
              DrawingHandler& drawingHandler, InputHandler& inputHandler,
              SoundHandler& soundHandler, ControlHandler& controlHandler,
              AiHandler& aiHandler, CollisionHandler& collisionHandler,
              ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler,
              PowerUpHandler& powerUpHandler, TimeHandler& timeHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
    int nextLevel();
};

#endif
