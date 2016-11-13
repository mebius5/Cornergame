#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onProj) :
    DynamicCollisionComponent(ent),
    projCollisionCommand(onProj),
    cameraShakeCommand(new CameraShakeCommand()) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->projCollisionCommand)
        delete this->projCollisionCommand;
    delete this->cameraShakeCommand;
}

void HeroCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (dynamic_cast<EnemyCollisionComponent*>(otherComp)) {
        Component::commandList->push_back(this->cameraShakeCommand);

    } else if (HeroCollisionComponent* otherHero =
               dynamic_cast<HeroCollisionComponent*>(otherComp)) {
        Component::commandList->push_back(this->cameraShakeCommand);
        // knock back the other hero
        otherHero->entity->physics->bump(this->sign(otherHero->entity->x + otherHero->entity->width/2 -
                                                    this->entity->x - this->entity->width/2));
    } else if (dynamic_cast<ProjectileCollisionComponent*>(otherComp)) {
        if (this->projCollisionCommand)
            Component::commandList->push_back(this->projCollisionCommand);
    }
}

void HeroCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    if (this->onGround || this->onLeftWall || this->onRightWall)
        this->entity->physics->resetJumps();
}
