#include "collisionComponent.h"

InfiniteJumpCollisionComponent::InfiniteJumpCollisionComponent(Entity *entity, Command * deleteEntityCmd):
    StaticCollisionComponent(entity),
    deletePowerUpCmd(deleteEntityCmd),
    isClaimed(false)
{
}

void InfiniteJumpCollisionComponent::onEntityCollision(DynamicCollisionComponent *otherComp, int) {
    if(!isClaimed){
        if(otherComp->entity->powerUp){
            otherComp->entity->powerUp->activateInfiniteJumpsPowerUp();
            Component::commandList->push_back(this->deletePowerUpCmd);
            isClaimed=true;
        }
    }
}

void InfiniteJumpCollisionComponent::onBorderCollision() {

}