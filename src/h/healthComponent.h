#ifndef CORNERGAME_HEALTH_COMPONENT_H
#define CORNERGAME_HEALTH_COMPONENT_H

#include "entity.h"
#include "component.h"

class HealthComponent : public Component {
    private:
        int health;
        int maxHealth;

    public:
        HealthComponent(Entity* entity, int maxHealth);
        ~HealthComponent();
        int getHealth();
        void takeDamage(int damage);
};

#endif
