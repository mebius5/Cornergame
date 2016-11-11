#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* cmd, int ownerID) :
    DynamicCollisionComponent(entity),
    despawnCommand(cmd),
    timeFreezeCommand(new TimeFreezeCommand(20)),
    ownerID(ownerID) {
}

ProjectileCollisionComponent::~ProjectileCollisionComponent() {
    if (this->despawnCommand)
        delete this->despawnCommand;
}

void ProjectileCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    // if we're frozen, we can only get picked up by heroes
    if (this->entity->physics->isFrozen() &&
            dynamic_cast<HeroCollisionComponent*>(otherComp)) {
        otherComp->entity->ammo->addAmmo(1);
        Component::commandList->push_back(this->despawnCommand);

    // if not frozen and collision with damagable, get destroyed and deal damage
    } else if (otherComp->entity->getId() != this->ownerID &&
            otherComp->entity->health) {
        otherComp->entity->health->takeDamage(250);
        otherComp->entity->actionState = DAMAGE;
        otherComp->entity->physics->bump(this->sign(this->entity->physics->xVelocity));
        Component::commandList->push_back(this->despawnCommand);
        Component::commandList->push_back(this->timeFreezeCommand);

    // if collision with owner, return as ammo
    } else if (otherComp->entity->getId() == this->ownerID) {
        otherComp->entity->ammo->addAmmo(1);
        Component::commandList->push_back(this->despawnCommand);
    }
}

void ProjectileCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    // only react to terrain, not other static objects
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        // stop moving
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
    }
}

void ProjectileCollisionComponent::onBorderCollision() {
}
