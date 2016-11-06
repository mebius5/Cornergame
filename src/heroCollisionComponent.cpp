#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEnemy) :
    DynamicCollisionComponent(ent),
    enemyCollisionCommand(onEnemy),
    cameraShakeCommand(new CameraShakeCommand()) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->enemyCollisionCommand)
        delete this->enemyCollisionCommand;
    delete this->cameraShakeCommand;
}

void HeroCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (dynamic_cast<EnemyCollisionComponent*>(otherComp)) {
        Component::commandList->push_back(this->cameraShakeCommand);
        this->entity->score->addScore(-10);
        if (this->enemyCollisionCommand)
            Component::commandList->push_back(this->enemyCollisionCommand);

    } else if (HeroCollisionComponent* otherHero =
               dynamic_cast<HeroCollisionComponent*>(otherComp)) {
        Component::commandList->push_back(this->cameraShakeCommand);
        // knock back the other hero
        otherHero->entity->physics->bump(this->sign(otherHero->entity->x + otherHero->entity->width/2 -
                                                    this->entity->x - this->entity->width/2));
    }
}

void HeroCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    if (this->onGround || this->onLeftWall || this->onRightWall)
        this->entity->physics->resetJumps();
}

void HeroCollisionComponent::onBorderCollision() {
}
