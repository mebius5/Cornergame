#ifndef CORNERGAME_ENTITY_MANAGER_H
#define CORNERGAME_ENTITY_MANAGER_H

#include <queue>
#include <map>
#include "entityBuilder.h"

class EntityManager {
private:
    EntityBuilder entityBuilder;
    std::queue<Entity*> deletionQueue;  // Entities waiting to be deleted
    int numCleanable;                   // # of entities ready for deletion
public:
    std::map<int, Entity*> entities;
    std::map<int, AiComponent*> aiComponents;
    std::map<int, ArtComponent*> artComponents;
    std::map<int, CollisionComponent*> collisionComponents;
    std::map<int, InputComponent*> inputComponents;
    std::map<int, PhysicsComponent*> physicsComponents;
    std::map<int, HealthComponent*> healthComponents;
    std::map<int, ScoreComponent*> scoreComponents;

    EntityManager(SDL_Renderer* renderer);
    ~EntityManager();

    void addEntity(Entity* entity);
    void deleteEntity(int id);
    void deleteEntity(Entity* entity);
    void cleanupEntities();
    void clear();

    Entity* createHero(int x, int y, const char* collisionSfxFile);
    Entity* createEnemy(int x, int y);
    Entity* createBackground(const char * filename, int width, int height);

    Entity* createHealthBar(int x, int y, int width, int height, Entity* owner);
    Entity* createScoreBox(int x, int y, Entity* owner);

    Entity* createCenteredFadeInText(const char *fontName,
                            const char *text, int fontSize, int r, int g, int b,
                            int initialAlpha, int windowW, int windowH);

    Entity* createHorizontallyCenteredFadeInText(const char *fontName,
                                             const char *text,
                                             int fontSize,
                                             int r, int g, int b, int initialAlpha,
                                             int windowW, int yPos,
                                             int index, int numOptions, StateEnum nextState);
};

#endif
