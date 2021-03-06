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
#include "particleHandler.h"

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
    virtual void begin(int level) = 0;
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
    PhysicsHandler& physicsHandler;
    ParticleHandler& particleHandler;
public:
    StartState(int windowW, int windowH, EntityManager& entityManager,
               std::vector<Command*>& commandList, SDL_Renderer* renderer,
               DrawingHandler& drawingHandler, InputHandler& inputHandler,
               SoundHandler& soundHandler, ControlHandler& controlHandler,
               CollisionHandler& collisionHandler, PhysicsHandler& physicsHandler, ParticleHandler& particleHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
};

class LevelSelectState : public State {
private:
    bool * levelSelected;
    DrawingHandler& drawingHandler;
    InputHandler& inputHandler;
    SoundHandler& soundHandler;
    ControlHandler& controlHandler;
public:
    LevelSelectState(int windowW, int windowH, bool *levelSelected, EntityManager &entityManager,
                         std::vector<Command *> &commandList, SDL_Renderer *renderer,
                         DrawingHandler &drawingHandler, InputHandler &inputHandler,
                         SoundHandler &soundHandler, ControlHandler &controlHandler);
    void begin(int level);
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
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
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
    ParticleHandler& particleHandler;
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
              ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler, ParticleHandler& particleHandler,
              PowerUpHandler& powerUpHandler, TimeHandler& timeHandler,
              ResultsState& resultsState, HighscoreState& highscoreState);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
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
    ParticleHandler& particleHandler;
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
              ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler, ParticleHandler& particleHandler,
              PowerUpHandler& powerUpHandler, TimeHandler& timeHandler);
    void begin(int level);
    StateEnum run();
    void cleanup(StateEnum next);
};

#endif
