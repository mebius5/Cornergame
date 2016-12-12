#include "collisionComponent.h"

BombCollisionComponent::BombCollisionComponent(Entity* entity) :
    DynamicCollisionComponent(entity),
    exploded(false),
    screenShakeCmd(new CameraShakeCommand()) {
}

BombCollisionComponent::~BombCollisionComponent() {
    delete this->screenShakeCmd;
}

void BombCollisionComponent::explode() {
    if (this->exploded)
        return;
    this->exploded = true;
    static_cast<OneTimeAnimationComponent*>(this->entity->art)->startAnimation();
    this->entity->x -= this->entity->width;
    this->entity->y -= this->entity->height*2;
    this->entity->width *= 3;
    this->entity->height *= 3;
    this->entity->drawX = this->entity->width/2 - this->entity->drawWidth/2;
    this->entity->drawY = this->entity->height/2 - this->entity->drawHeight/2;
    Component::commandList->push_back(this->screenShakeCmd);
}

void BombCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (otherComp->entity->health) {
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
        this->explode();
        otherComp->entity->health->splash = true;
        this->entity->particle->setIndefSpawn(false);
        otherComp->entity->actionState = ACTION_DAMAGE;
    }
}

void BombCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
        this->explode();
        this->entity->particle->setIndefSpawn(false);
    }
}
