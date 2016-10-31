#ifndef CORNERGAME_AMMO_COMPONENT_H
#define CORNERGAME_AMMO_COMPONENT_H

#include "entity.h"
#include "component.h"

class AmmoComponent : public Component {
private:
    int ammo;
    int maxAmmo;
    bool isUnlimited;

public:
    AmmoComponent(Entity* entity, int maxAmmo);
    ~AmmoComponent();
    int getAmmo();
    int getMaxAmmo();
    void spendAmmo();
    void toggleUnlimited();
    bool hasAmmo();
    void addAmmo(int amount);
};

#endif
