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
    std::queue<Entity*> deletionQueue;
    int numCleanable;                   // # of entities ready for deletion
public:
    std::vector<AiComponent*> aiComponents;
    std::vector<ArtComponent*> artComponents;
    std::vector<StaticCollisionComponent*> staticCollisionComponents;
    std::vector<DynamicCollisionComponent*> dynamicCollisionComponents;
    std::vector<InputComponent*> inputComponents;
    std::vector<PhysicsComponent*> physicsComponents;
    std::vector<HealthComponent*> healthComponents;
    std::vector<ScoreComponent*> scoreComponents;
    std::vector<PowerUpComponent*> powerUpComponents;
    std::vector<Entity *> heroEntities;
    std::vector<PowerUpCollisionComponent*> powerUpCollisionComponents;

    EntityManager(SDL_Renderer *renderer, std::vector<Command *> &cmdList);
    ~EntityManager();

    void addEntity(Entity* entity);     // add entity/components to map/vectors
    void deleteEntity(int id);          // put entity on queue for deletion on
    void cleanupEntities();             // delete entities when ready
    void clear();                       // delete all entities

    Entity* createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd);
    Entity* createEnemy(TextureEnum texType, int x, int y);
    Entity* createBackground(TextureEnum texType, int width, int height);
    Entity* createHealthBar(int x, int y, Entity* owner);
    Entity* createAmmoBar(int x, int y, Entity* owner);
    Entity* createScoreBox(int x, int y, Entity* owner);

    Entity* createCenteredFadeInText(FontEnum font,
                            const char* text, int fontSize, int r, int g, int b,
                            int initialAlpha, int windowW, int windowH);

    Entity* createHorizontallyCenteredFadeInText(FontEnum font,
                                                     const char *text, int fontSize,
                                                     int r, int g, int b, int initialAlpha,
                                                     int windowW, int yPos);

    Entity* createHorizontallyCenteredFadeInMenuText(FontEnum font,
                                                     const char *text, int fontSize,
                                                     int r, int g, int b, int initialAlpha,
                                                     int windowW, int yPos,
                                                     int index, int numOptions, StateEnum nextState);
    Entity* createVictoryZone(int x, int y);
    Entity* createPowerUp(TextureEnum pwrUpType, int x, int y);
    Entity* createStaticBackgroundObject(TextureEnum texType, int x, int y);
    Entity * createTerrain(Tiles tileType, int x, int y, int numberHorizontal, bool freeTop, bool freeBot,
        bool freeRight, bool freeLeft);
    Entity* createProjectile(int x, int y, float charge, int dir, int ownerID, ProjEnum projType);
    void handleSpawns();
    void populateLevel(Level * level);
    void printCommands();
};

#endif
