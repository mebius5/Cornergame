#include "aiComponent.h"

EnemyAiComponent::EnemyAiComponent(Entity* entity) :
    AiComponent(entity),
    timeElapsed(1500),
    speed(.1f) {
}

// picks a behavior at random, and keeps it until timer resets
void EnemyAiComponent::updateLocation(int dt) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= 1500) {
        this->entity->xVelocity = (rand() % 3 - 1) * speed; // pick 1, 0 or -1
        this->entity->yVelocity = (rand() % 3 - 1) * speed; //  for scaling x, y
        this->timeElapsed = 0;
    }

    this->entity->x += this->entity->xVelocity * dt;
    this->entity->y += this->entity->yVelocity * dt;
}

// force the entity to pick a new behavior
void EnemyAiComponent::resetAi() {
    this->timeElapsed = 1500;
}
