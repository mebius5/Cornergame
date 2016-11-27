#include "collisionComponent.h"

BounceCollisionComponent::BounceCollisionComponent(Entity *entity):
    StaticCollisionComponent(entity),
    bounceCommand(new PlaySoundCommand(SFX_BOUNCE)),
    bounceVelocity(1.0f) {
}

BounceCollisionComponent::~BounceCollisionComponent() {
    if (this->bounceCommand)
        delete this->bounceCommand;
}

void BounceCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    // move it above
    otherComp->entity->y = this->entity->y - otherComp->entity->height;
    // bounce the thing upwards
    otherComp->entity->physics->resetJumps();
    otherComp->entity->physics->jump(this->bounceVelocity);
    this->entity->actionState = ACTION_JUMP;
    BounceAnimationComponent* aniComp = dynamic_cast<BounceAnimationComponent*>(this->entity->art);
    aniComp->restartAnimation();
}
