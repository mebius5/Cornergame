#ifndef CORNERGAME_AMMO_COMPONENT_H
#define CORNERGAME_AMMO_COMPONENT_H

#include "entity.h"
#include "component.h"

class AmmoComponent : public Component {
private:
    int ammo;
    int maxAmmo;
    SpawnProjCommand* spawnCommand;
    SpawnProjCommand* bombCommand;
    bool hasBomb;
    bool isUnlimited;

public:
    AmmoComponent(Entity* entity, int maxAmmo);
    ~AmmoComponent();
    int getAmmo();
    int getMaxAmmo();
    void spendAmmo(float charge);
    void toggleUnlimited();
    void addAmmo(int amount);
    void addBomb();
};

#endif
