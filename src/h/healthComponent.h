#ifndef CORNERGAME_HEALTH_COMPONENT_H
#define CORNERGAME_HEALTH_COMPONENT_H

#include "entity.h"
#include "component.h"

class HealthComponent : public Component {
private:
    int health;
    int maxHealth;
    Command* onDeath;
public:
    HealthComponent(Entity* entity, int maxHealth, Command* onDeath);
    ~HealthComponent();
    int getHealth();
    int getMaxHealth();
    void takeDamage(int damage);
};

#endif
