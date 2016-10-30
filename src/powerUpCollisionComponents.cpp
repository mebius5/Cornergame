#include "collisionComponent.h"

PowerUpCollisionComponent::PowerUpCollisionComponent(Entity *entity, Command *deletePwrUpEntityCmd):
        StaticCollisionComponent(entity),
        deletePowerUpCmd(deletePwrUpEntityCmd),
        isClaimed(false)
{
}

InfiniteJumpCollisionComponent::InfiniteJumpCollisionComponent(Entity *entity, Command * deletePwrUpEntityCmd):
        PowerUpCollisionComponent(entity, deletePwrUpEntityCmd)
{
}

void InfiniteJumpCollisionComponent::onEntityCollision(DynamicCollisionComponent *otherComp, int) {
    if(!isClaimed){
        if(otherComp->entity->powerUp){
            otherComp->entity->powerUp->activateInfJumpPwrUp();
            Component::commandList->push_back(this->deletePowerUpCmd);
            isClaimed=true;
        }
    }
}

void InfiniteJumpCollisionComponent::onBorderCollision() {

}

void InfiniteHealthCollisionComponent::onEntityCollision(DynamicCollisionComponent *otherComp, int) {
    if(!isClaimed){
        if(otherComp->entity->powerUp){
            otherComp->entity->powerUp->activateInfHealthPwrUp();
            Component::commandList->push_back(this->deletePowerUpCmd);
            isClaimed=true;
        }
    }
}

void InfiniteHealthCollisionComponent::onBorderCollision() {

}