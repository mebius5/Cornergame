#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
    DynamicCollisionComponent(ent),
    entityCollisionCommand(onEntity),
    timeSinceLastCollision(0) {
        this->cameraShakeCommand = new CameraShakeCommand();
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
    delete this->cameraShakeCommand;
}

void HeroCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp, int dt) {
    // shake camera
    Component::commandList->push_back(this->cameraShakeCommand);

    if (dynamic_cast<EnemyCollisionComponent*>(otherComp)) {
        timeSinceLastCollision+=dt;

        if (timeSinceLastCollision>=30) {
            timeSinceLastCollision=0;
            this->entity->score->addScore(-10);
            this->entity->health->takeDamage(7);
            this->entity->actionState = DAMAGE;
            if (this->entityCollisionCommand)
                Component::commandList->push_back(this->entityCollisionCommand);
        }

    } else if (ProjectileCollisionComponent* projectile =
                   dynamic_cast<ProjectileCollisionComponent*>(otherComp)) {
        if (projectile->ownerID != this->entity->getId()) {
            this->entity->health->takeDamage(10);
        }

    } else if (HeroCollisionComponent* otherHero =
               dynamic_cast<HeroCollisionComponent*>(otherComp)) {
        // knock back the other hero
        otherHero->entity->physics->bump(this->sign(otherHero->entity->x + otherHero->entity->width/2 -
                                                    this->entity->x - this->entity->width/2));
    }

}

void HeroCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    if (this->onGround || this->onLeftWall || this->onRightWall)
        ((PhysicsComponent*)this->entity->physics)->resetJumps();
}

void HeroCollisionComponent::onBorderCollision() {
}
