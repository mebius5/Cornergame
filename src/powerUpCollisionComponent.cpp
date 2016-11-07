#include "collisionComponent.h"

PowerUpCollisionComponent::PowerUpCollisionComponent(Entity *entity,
                                                     TextureEnum pwrUpType,
                                                     SfxEnum pwrSound):
    StaticCollisionComponent(entity),
    pickupCommand(new PlaySoundCommand(pwrSound)),
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
        if (this->pickupCommand)
            Component::commandList->push_back(this->pickupCommand);
    }
}

void PowerUpCollisionComponent::onBorderCollision() {
}

void PowerUpCollisionComponent::setIsClaimed(bool isClaimed) {
    this->isClaimed = isClaimed;
}
