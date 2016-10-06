#include "healthComponent.h"

HealthComponent::HealthComponent(Entity * entity, int maxHealth):
    Component(entity),
    health(maxHealth),
    maxHealth(maxHealth) {
}

HealthComponent::~HealthComponent() {
    this->entity = NULL;
}

int HealthComponent::getHealth() {
    return this->health;
}

int HealthComponent::getMaxHealth() {
    return this->maxHealth;
}

void HealthComponent::takeDamage(int damage) {
    this->health -= damage;
}
