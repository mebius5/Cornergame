#include "entity.h"

RespawnEntity::RespawnEntity(int id, float x, float y, int w, int h,
                             int drawWidth, int drawHeight) :
    Entity(id, x, y, w, h, drawWidth, drawHeight),
    initialX(x),
    initialY(y),
    shifted(false) {
}
