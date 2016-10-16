#include "aiComponent.h"

EnemyAiComponent::EnemyAiComponent(Entity* entity, std::vector<Entity *> * heroEntities) :
    AiComponent(entity),
    timeElapsed(1500),
    speed(.1f),
    heroEntities(heroEntities){
}

// picks a behavior at random, and keeps it until timer resets
void EnemyAiComponent::updateLocation(int dt) {
    std::vector<Entity*>::iterator heroInIt;
    int minDistance = 100000;
    for (heroInIt = this->heroEntities->begin(); heroInIt != this->heroEntities->end(); ) {
        if((*heroInIt)){
            int distance = sqrt(((*heroInIt)->x - this->entity->x ) * ((*heroInIt)->x - this->entity->x) +
                                ((*heroInIt)->y - this->entity->y ) * ((*heroInIt)->y - this->entity->y));

            //If the enemy gets within 300 pixel and is the hero is the closest hero to the enemy
            //Then we update the distance of the enemy with respect to the location of the hero
            //Else the movement is random
            if( distance < 300 && distance<minDistance){
                update(dt, (*heroInIt));
                minDistance=distance;
            } else{
                update(dt, NULL);
            }
            ++heroInIt;
        }
    }
}

void EnemyAiComponent::update(int dt, Entity *hero) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= 750) {
        if(hero!=NULL){
            int xNewDir = (hero->x - this->entity->x);//*(this->entity->xVelocity);
            if(xNewDir>0){
                this->entity->xVelocity=1*speed;
            } else if (xNewDir<=0){
                this->entity->xVelocity=-1*speed;
            }
            int yNewDir = (hero->y - this->entity->y);//*(this->entity->yVelocity);
            if(yNewDir>0){
                this->entity->yVelocity=1*speed;
            } else if (yNewDir<=0){
                this->entity->yVelocity=-1*speed;
            }
        } else{
            this->entity->xVelocity = (rand() % 3 - 1) * speed; // pick 1, 0 or -1
            this->entity->yVelocity = (rand() % 3 - 1) * speed; //  for scaling x, y
        }
        this->timeElapsed = 0;
    }

    this->entity->x += this->entity->xVelocity * dt;
    this->entity->y += this->entity->yVelocity * dt;
}

// force the entity to pick a new behavior
void EnemyAiComponent::resetAi() {
    this->timeElapsed = 1500;
}
