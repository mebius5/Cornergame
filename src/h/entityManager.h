#ifndef CORNERGAME_ENTITY_MANAGER_H
#define CORNERGAME_ENTITY_MANAGER_H

#include <queue>
#include <unordered_map>
#include <vector>
#include "entityBuilder.h"
#include "level.h"
#include "enums.h"

class EntityManager {
private:
    std::vector<Command*>& commandList;
    std::unordered_map<int, Entity*> entityMap;
    EntityBuilder entityBuilder;
    std::queue<Entity*> deletionQueue;  // Entities waiting to be deleted
    int numCleanable;                   // # of entities ready for deletion
public:
    std::vector<AiComponent*> aiComponents;
    std::vector<ArtComponent*> artComponents;
    std::vector<CollisionComponent*> staticCollisionComponents;
    std::vector<CollisionComponent*> volatileCollisionComponents;
    std::vector<InputComponent*> inputComponents;
    std::vector<PhysicsComponent*> physicsComponents;
    std::vector<HealthComponent*> healthComponents;
    std::vector<ScoreComponent*> scoreComponents;
    std::vector<Entity *> heroEntities;

    EntityManager(SDL_Renderer* renderer, std::vector<Command*>& cmdList);
    ~EntityManager();

    void addEntity(Entity* entity);     // add entity/components to map/vectors
    void deleteEntity(int id);          // put entity on queue for deletion on
    void deleteEntity(Entity* entity);  //  next round (allows commands to run)
    void cleanupEntities();             // delete entities when ready
    void clear();                       // delete all entities

    Entity* createHero(int x, int y, SfxEnum sfxType, bool wasd);
    Entity* createEnemy(int x, int y);
    Entity* createBackground(const char * filename, int width, int height);

    Entity* createHealthBar(int x, int y, int width, int height, Entity* owner);
    Entity* createScoreBox(int x, int y, Entity* owner);

    Entity* createCenteredFadeInText(const char *fontName,
                            const char *text, int fontSize, int r, int g, int b,
                            int initialAlpha, int windowW, int windowH);

    Entity* createHorizontallyCenteredFadeInText(const char *fontName,
                            const char *text, int fontSize,
                            int r, int g, int b, int initialAlpha,
                            int windowW, int yPos,
                            int index, int numOptions, StateEnum nextState);
    Entity* createVictoryZone(int x, int y);
    Entity * createTerrain(int x, int y, bool freeTop, bool freeBot,
        bool freeRight, bool freeLeft);
    Entity* createProjectile(int x, int y, ProjEnum projType);
    void handleSpawns();
    void populateLevel(Level * level);
};

#endif
