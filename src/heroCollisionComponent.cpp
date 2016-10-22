#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
        CollisionComponent(ent, false),
        entityCollisionCommand(onEntity), timeSinceLastCollision(0) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void HeroCollisionComponent::onEntityCollision(Entity *other, int dt) {
    if(dynamic_cast<EnemyCollisionComponent*>(other->collision)){

        timeSinceLastCollision+=dt;

        if(timeSinceLastCollision>=30){
            timeSinceLastCollision=0;
            this->entity->score->addScore(-10);
            this->entity->health->takeDamage(5);
            if (this->entityCollisionCommand)
                Component::commandList->push_back(this->entityCollisionCommand);
        }

    } else if (ProjectileCollisionComponent* projectile =
                   dynamic_cast<ProjectileCollisionComponent*>(other->collision)) {
        if (projectile->ownerID != this->entity->getId()) {
            this->entity->health->takeDamage(10);
        }
    }
}

void HeroCollisionComponent::onStaticCollision(Entity *) {
    if (this->entity->physics->yVelocity > 0)
        ((PhysicsComponent*)this->entity->physics)->resetJumps();
}

void HeroCollisionComponent::onBorderCollision() {
}
