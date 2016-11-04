#include "healthComponent.h"

HealthComponent::HealthComponent(Entity * entity, int maxHealth, Command* onDeath):
    Component(entity),
    health(maxHealth),
    maxHealth(maxHealth),
    isInvincible(false),
    onDeath(onDeath) {
}

HealthComponent::~HealthComponent() {
    this->entity = NULL;
    if (this->onDeath)
        delete this->onDeath;
}

int HealthComponent::getHealth() {
    return this->health;
}

int HealthComponent::getMaxHealth() {
    return this->maxHealth;
}

void HealthComponent::toggleInvincibility() {
    this->isInvincible= !this->isInvincible;
}

void HealthComponent::takeDamage(int damage) {
    if(!this->isInvincible){
        this->health -= damage;
        if (this->health <= 0 && this->onDeath)
            Component::commandList->push_back(this->onDeath);
    }
}

void HealthComponent::die() {
    this->health = 0;
    Component::commandList->push_back(this->onDeath);
}

bool HealthComponent::isIsInvincible() const {
    return isInvincible;
}

void HealthComponent::setIsInvincible(bool isInvincible) {
    HealthComponent::isInvincible = isInvincible;
}
