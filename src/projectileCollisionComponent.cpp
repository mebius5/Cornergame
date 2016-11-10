#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* cmd, int ownerID) :
    DynamicCollisionComponent(entity),
    despawnCommand(cmd),
    ownerID(ownerID) {
}

ProjectileCollisionComponent::~ProjectileCollisionComponent() {
    if (this->despawnCommand)
        delete this->despawnCommand;
}

void ProjectileCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    // if we're frozen, we can only get picked up by heros
    if (this->entity->physics->isFrozen()) {
        if (dynamic_cast<HeroCollisionComponent*>(otherComp)) {
            otherComp->entity->ammo->addAmmo(1);
            Component::commandList->push_back(this->despawnCommand);
        }

    // if not frozen, get destroyed and deal damage
    } else if (otherComp->entity->getId() != this->ownerID) {
        Component::commandList->push_back(this->despawnCommand);
        if (otherComp->entity->health) {
            otherComp->entity->health->takeDamage(250);
            otherComp->entity->actionState = DAMAGE;
        }
        otherComp->entity->physics->bump(this->sign(this->entity->physics->xVelocity));
    }
}

void ProjectileCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    // only react to terrain, not other static objects
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        // stop moving
        this->entity->physics->freeze();
    }
}

void ProjectileCollisionComponent::onBorderCollision() {
}
