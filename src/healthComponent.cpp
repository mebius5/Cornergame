#include "healthComponent.h"

HealthComponent::HealthComponent(Entity * entity, int maxHealth, Command* onDeath):
    Component(entity),
    health(maxHealth),
    maxHealth(maxHealth),
    isInvincible(false),
    onDeath(onDeath),
    splash(false) {
}

HealthComponent::~HealthComponent() {
    this->entity = NULL;
    if (this->onDeath){
        delete this->onDeath;
        this->onDeath = NULL;
    }
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
        if (this->health <= 0)
            Component::commandList->push_back(this->onDeath);
    }
}

void HealthComponent::takeUnblockableDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0)
        Component::commandList->push_back(this->onDeath);
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

void HealthComponent::replaceOnDeathCommand(Command *newOnDeath) {
    if (this->onDeath){
        delete this->onDeath;
        this->onDeath = NULL;
    }
    this->onDeath = newOnDeath;
}
