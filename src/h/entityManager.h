#ifndef CORNERGAME_ENTITY_MANAGER_H
#define CORNERGAME_ENTITY_MANAGER_H

#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <array>
#include "entityBuilder.h"
#include "level.h"
#include "consts.h"

class EntityManager {
private:
    std::vector<Command*>& commandList;
    std::unordered_map<int, Entity*> entityMap;
    EntityBuilder entityBuilder;
    std::queue<Entity*> deletionQueue;
    int windowW;
    int numCleanable;                   // # of entities ready for deletion
    void initIndices();
public:
    std::vector<AiComponent*> aiComponents;
    std::vector<ArtComponent*> artComponents;  // in order by layer #
    std::array<int, NLAYERS> layerIndices;   // indices of last item w/ given layer
    std::vector<BackgroundArtComponent*> bgComponents;
    std::vector<StaticCollisionComponent*> staticCollisionComponents;
    std::vector<DynamicCollisionComponent*> dynamicCollisionComponents;
    std::vector<InputComponent*> inputComponents;
    std::vector<PhysicsComponent*> physicsComponents;
    std::vector<ParticleComponent*> particleComponents;
    std::vector<HealthComponent*> healthComponents;
    std::vector<ScoreComponent*> scoreComponents;
    std::vector<PowerUpComponent*> powerUpComponents;
    std::vector<Entity*> heroEntities;
    std::vector<RespawnEntity*> respawnEntities;
    std::vector<PowerUpCollisionComponent*> powerUpCollisionComponents;
    std::vector<FadingTerrainColComponent*> fadingTerrainColComponents;

    EntityManager(SDL_Renderer *renderer, std::vector<Command *> &cmdList, int windowW);
    ~EntityManager();

    void addEntity(Entity* entity);     // add entity/components to map/vectors
    void initRespawns();                // note which entities can respawn (dynamic only)
    Entity* hideEntity(int id);         // remove entity from lists, but don't delete
    void deleteEntity(int id);          // put entity on queue for deletion on next round
    void cleanupEntities();             // delete entities when ready
    void clear();                       // delete all entities

    Entity *createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd);
    Entity* createEnemy(TextureEnum texType, int x, int y);
    Entity* createBackground(TextureEnum texType, int x, int y, int w, int h, float speed);
    Entity* createHealthBar(int x, int y, Entity* owner);
    Entity* createHealthBarOverlay(int x, int y, TextureEnum texType);
    Entity* createAmmoBar(int x, int y, Entity* owner);
    // Entity* createScoreBox(int x, int y, Entity* owner);

    void createFadeInText(FontEnum font, const char* text, int fontSize, int r, int g, int b,
                             int initialAlpha, int windowW, int x, int y);

    void createCenteredFadeInText(FontEnum font, const char* text, int fontSize, int r, int g, int b,
                                     int initialAlpha, int windowW, int windowH);

    void createHorizontallyCenteredFadeInText(FontEnum font, const char *text, int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int yPos);

    Entity* createHorizontallyCenteredFadeInMenuText(FontEnum font, const char *text, int fontSize,
                                                     int r, int g, int b, int initialAlpha,
                                                     int windowW, int yPos,
                                                     int index, int numOptions, StateEnum nextState);
    Entity* createHorizontallyCenteredSelectLevelText(FontEnum fontType,
                                                      const char *text, int fontSize,
                                                      int r, int g, int b, int initialAlpha,
                                                      int windowW, int yPos,
                                                      int index, int numOptions,
                                                      StateEnum nextState, bool * levelSelected);
    Entity* createLevelPreview(TextureEnum tex, int x, int y);
    Entity* createVictoryZone(int x, int y);
    Entity* createPowerUp(TextureEnum pwrUpType, SfxEnum pwrSound, int x, int y);
    Entity* createParticle(int x, int y);
    Entity* createStaticBackgroundObject(TextureEnum texType, int x, int y);
    Entity* createAnimatedBackgroundObject(TextureEnum texType, int x, int y, int fps, int numFrames);
    //Entity* createStaticBackgroundObject(TextureEnum texType, TextureEnum lightType, int x, int y);
    Entity* createTerrain(Tile tileType, int x, int y, int numberHorizontal, bool freeTop, bool freeBot,
        bool freeRight, bool freeLeft);
    Entity* createBounce(TextureEnum tileType, int x, int y);
    Entity* createProjectile(int x, int y, float charge, int dir, int ownerID, ProjEnum projType);
    void setLightTexture(Entity * entity, TextureEnum lightTex, bool addTrueModFalse);
    void handleSpawns();
    void populateLevel(Level* level);
    void printCommands();
};

#endif
