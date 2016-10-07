#include "entityManager.h"

/* Constructor and Destructor */
EntityManager::EntityManager(SDL_Renderer* renderer) :
    entityBuilder(renderer),
    numCleanable(0) {
}

EntityManager::~EntityManager() {
    this->clear();
}

/* Entity Insertion and Deletion */
void EntityManager::addEntity(Entity* entity) {
    int id = entity->getId();
    this->entities[id] = entity;

    if (entity->ai)
        this->aiComponents[id] = entity->ai;
    if (entity->art)
        this->artComponents[id] = entity->art;
    if (entity->collision)
        this->collisionComponents[id] = entity->collision;
    if (entity->input)
        this->inputComponents[id] = entity->input;
    if (entity->physics)
        this->physicsComponents[id] = entity->physics;
    if (entity->health)
        this->healthComponents[id] = entity->health;
    if (entity->score)
        this->scoreComponents[id] = entity->score;
}

void EntityManager::deleteEntity(Entity* entity) {
    int id = entity->getId();
    this->entities.erase(id);
    this->aiComponents.erase(id);
    this->artComponents.erase(id);
    this->collisionComponents.erase(id);
    this->inputComponents.erase(id);
    this->physicsComponents.erase(id);
    this->healthComponents.erase(id);
    this->scoreComponents.erase(id);
    this->deletionQueue.push(entity);
}

void EntityManager::deleteEntity(int id) {
    this->deleteEntity(this->entities[id]);
}

void EntityManager::cleanupEntities() {
    for (int i = 0; i < this->numCleanable; i++) {
        Entity* entity = this->deletionQueue.front();
        this->deletionQueue.pop();
        delete entity;
    }

    this->numCleanable = this->deletionQueue.size();
}

void EntityManager::clear() {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entities.begin(); it != this->entities.end(); ++it)
        delete it->second;      // delete all Entities from map
    this->entities.clear();
    this->aiComponents.clear();
    this->artComponents.clear();
    this->collisionComponents.clear();
    this->inputComponents.clear();
    this->physicsComponents.clear();
    this->healthComponents.clear();
    this->scoreComponents.clear();
}

/* Entity Creation Methods */
Entity* EntityManager::createHero(int x, int y, SfxEnum sfxType) {
    Entity* entity = this->entityBuilder.createHero(x, y, sfxType);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createEnemy(int x, int y) {
    Entity* entity = this->entityBuilder.createEnemy(x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createBackground(const char* filename, int w, int h) {
    Entity* entity = this->entityBuilder.createBackground(filename, w, h);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHealthBar(int x, int y, int width, int height, Entity* owner) {
    Entity* entity = this->entityBuilder.createHealthBar(x, y, width, height, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createScoreBox(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createScoreBox(x, y, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createCenteredFadeInText(const char* fontName,
                        const char* text, int fontSize, int r, int g, int b,
                        int initialAlpha, int windowW, int windowH) {

    Entity* entity = this->entityBuilder.createCenteredFadeInText(fontName,
                            text, fontSize, r, g, b,
                            initialAlpha, windowW, windowH);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHorizontallyCenteredFadeInText(const char* fontName,
                                                 const char* text,
                                                 int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int yPos,
                                                 int index, int numOptions, StateEnum nextState) {
    Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInText(
        fontName, text, fontSize, r, g, b, initialAlpha,
        windowW, yPos, index, numOptions, nextState);
    this->addEntity(entity);
    return entity;
}
