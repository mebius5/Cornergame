#include "collisionComponent.h"

PowerUpCollisionComponent::PowerUpCollisionComponent(Entity *entity, Command *deletePwrUpEntityCmd,
                                                     PowerUpType pwrUpType):
        StaticCollisionComponent(entity),
        deletePowerUpCmd(deletePwrUpEntityCmd),
        isClaimed(false),
        pwrUpType(pwrUpType)
{

}

void PowerUpCollisionComponent::onEntityCollision(DynamicCollisionComponent *otherComp, int) {
    if(!isClaimed){
        if(otherComp->entity->powerUp){
            otherComp->entity->powerUp->activatePowerUp(this->pwrUpType);
            Component::commandList->push_back(this->deletePowerUpCmd);
            isClaimed=true;
        }
    }
}

void PowerUpCollisionComponent::onBorderCollision() {
}