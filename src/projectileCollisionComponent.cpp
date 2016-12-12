#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* cmd, int ownerID) :
    DynamicCollisionComponent(entity),
    despawnCommand(cmd),
    timeFreezeCommand(new TimeFreezeCommand(20)),
    timeNormalCommand(new TimeNormalCommand()),
    ownerID(ownerID) {
}

ProjectileCollisionComponent::~ProjectileCollisionComponent() {
    if (this->despawnCommand)
        delete this->despawnCommand;
    delete this->timeFreezeCommand;
    delete this->timeNormalCommand;
}

void ProjectileCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    // if we're frozen, we can only get picked up by heroes
    if (this->entity->physics->isFrozen() &&
            dynamic_cast<HeroCollisionComponent*>(otherComp)) {
        otherComp->entity->ammo->addAmmo(1);
        Component::commandList->push_back(this->despawnCommand);
        this->entity->particle->setIndefSpawn(false);

    // if not frozen and collision with damagable, get destroyed and deal damage
    } else if (otherComp->entity->getId() != this->ownerID &&
            otherComp->entity->health) {
        if (otherComp->entity->physics->dodgeTime > otherComp->entity->physics->maxDodgeTime/3) {
            otherComp->entity->ammo->addAmmo(1);
        } else {
            otherComp->entity->health->takeDamage(250);
            otherComp->entity->actionState = ACTION_DAMAGE;
            otherComp->entity->physics->bump(this->sign(this->entity->physics->xVelocity));
        }
        Component::commandList->push_back(this->despawnCommand);
        Component::commandList->push_back(this->timeFreezeCommand);
        Component::commandList->push_back(this->timeNormalCommand);
        this->entity->particle->setIndefSpawn(false);
        this->entity->physics->disableSlow();
    // if collision with owner, return as ammo
    } else if (otherComp->entity->getId() == this->ownerID) {
        otherComp->entity->ammo->addAmmo(1);
        Component::commandList->push_back(this->despawnCommand);
        this->entity->particle->setIndefSpawn(false);
    }
}

void ProjectileCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    // only react to terrain, not other static objects
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        // create dust if first collision
        if (!this->entity->physics->isFrozen()) {
            this->entity->particle->startSpawning(80, 120);
        }
        // stop moving
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
        this->entity->particle->setIndefSpawn(false);
    }
}
