#include "aiComponent.h"

EnemyAiComponent::EnemyAiComponent(Entity* entity, std::vector<Entity*>* heroEntities) :
    AiComponent(entity),
    timeElapsed(1500),
    heroEntities(heroEntities) {
}

void EnemyAiComponent::updateLocation(int dt) {
    this->timeElapsed += dt;
    if (this->timeElapsed < 750)
        return;

    std::vector<Entity*>::iterator it;
    int minDistance = 100000;
    Entity* closestHero = NULL;
    for (it = this->heroEntities->begin(); it != this->heroEntities->end(); ++it) {
        Entity* hero = *it;
        int sqnorm = (hero->x - this->entity->x) * (hero->x - this->entity->x)
                     + (hero->y - this->entity->y) * (hero->y - this->entity->y);

        //If the enemy gets within 300 pixel and is the hero is the closest hero to the enemy
        //Then we update the distance of the enemy with respect to the location of the hero
        //Else the movement is random
        if (sqnorm < 90000 && sqnorm < minDistance) {
            closestHero = hero;
            minDistance = sqnorm;
        }
    }
    this->update(closestHero);
    this->timeElapsed = 0;
}

void EnemyAiComponent::update(Entity *hero) {
    if (hero != NULL) {
        int xNewDir = (hero->x - this->entity->x);
        if (xNewDir > 0) {
            this->entity->physics->xVelocity = this->entity->physics->maxXVelocity;
            this->entity->dir = 1;
        } else {
            this->entity->physics->xVelocity = -this->entity->physics->maxXVelocity;
            this->entity->dir = -1;
        }
        int yNewDir = (hero->y - this->entity->y);
        if (yNewDir < 0) {
            this->entity->physics->jump();
        }
    } else {
        this->entity->dir = (rand() % 2) * 2 - 1;       // pick 1 or -1
        this->entity->physics->bump(this->entity->dir);
        if (rand() % 3 == 0) {
            this->entity->physics->jump();
        }
    }
}

// force the entity to pick a new behavior
void EnemyAiComponent::resetAi() {
    this->timeElapsed = 1500;
}
