#ifndef CORNERGAME_HEALTH_COMPONENT_H
#define CORNERGAME_HEALTH_COMPONENT_H

#include "entity.h"
#include "component.h"

class HealthComponent : public Component {
private:
    int health;
    int maxHealth;
    bool isInvincible;
public:
    bool isIsInvincible() const;

    void setIsInvincible(bool isInvincible);

private:
    Command* onDeath;
public:
    HealthComponent(Entity* entity, int maxHealth, Command* onDeath);
    ~HealthComponent();
    int getHealth();
    int getMaxHealth();
    void toggleInvincibility();
    void takeDamage(int damage);
    void die();
};

#endif
