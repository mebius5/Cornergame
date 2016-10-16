#include "aiComponent.h"
#include "iostream"

ProjectileAiComponent::ProjectileAiComponent(Entity* entity) :
    AiComponent(entity) {
}

ProjectileAiComponent::~ProjectileAiComponent() {
    this->entity = NULL;
}
void ProjectileAiComponent::updateLocation(int dt) {
    this->entity->x += this->entity->xVelocity * dt;
    this->entity->y += this->entity->yVelocity * dt;
}
void ProjectileAiComponent::resetAi() {
}