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
}

int HealthComponent::getHealth() {
    return this->health;
}

int HealthComponent::getMaxHealth() {
    return this->maxHealth;
}

void HealthComponent::toggleInvincibility() {
    if(this->isInvincible){
        this->isInvincible=false;
    } else{
        this->isInvincible=true;
    }
}

void HealthComponent::takeDamage(int damage) {
    if(!this->isInvincible){
        this->health -= damage;
        if (this->health <= 0 && this->onDeath)
            Component::commandList->push_back(this->onDeath);
    }
}
