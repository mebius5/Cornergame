#include "collisionComponent.h"

FadingTerrainColComponent::FadingTerrainColComponent(Entity *entity, bool top, bool bot, bool r, bool l):
    TerrainCollisionComponent(entity,top,bot,r,l),
    hasDisappeared(false),
    touched(false),
    heroOtherComp1(NULL),
    heroOtherComp2(NULL)
{

}

void FadingTerrainColComponent::setHasDisappeared(bool hasDisappeared) {
    this->hasDisappeared = hasDisappeared;
    if(this->heroOtherComp1){
        this->heroOtherComp1->onGround=false;
    }
    if(this->heroOtherComp2){
        this->heroOtherComp2->onGround=false;
    }
}

void FadingTerrainColComponent::onEntityCollision(DynamicCollisionComponent *otherComp) {
    if(this->hasDisappeared){
        return;
    }
    if(!this->touched&& dynamic_cast<HeroCollisionComponent*>(otherComp)){
        this->touched= true;
        if(heroOtherComp1==NULL){
            heroOtherComp1=otherComp;
        } else {
            if(heroOtherComp1!=otherComp){
                heroOtherComp2=otherComp;
            }
        }
        if(FadingTerrainArtComponent * fa = dynamic_cast<FadingTerrainArtComponent * >(this->entity->art)){
            fa->startShake();
        }
    }
    TerrainCollisionComponent::onEntityCollision(otherComp);
}


