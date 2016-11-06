#include "collisionComponent.h"

PowerUpCollisionComponent::PowerUpCollisionComponent(Entity *entity, Command *deletePwrUpEntityCmd,
                                                     PowerUpType pwrUpType):
    StaticCollisionComponent(entity),
    deletePowerUpCmd(deletePwrUpEntityCmd),
    isClaimed(false),
    pwrUpType(pwrUpType) {
}

void PowerUpCollisionComponent::onEntityCollision(DynamicCollisionComponent *otherComp) {
    if(isClaimed)
        return;

    if(otherComp->entity->powerUp){
        otherComp->entity->powerUp->activatePowerUp(this->pwrUpType);
        this->entity->art->isVisible=false;
        isClaimed=true;
    }
}

void PowerUpCollisionComponent::onBorderCollision() {
}

void PowerUpCollisionComponent::setIsClaimed(bool isClaimed) {
    this->isClaimed = isClaimed;
}
