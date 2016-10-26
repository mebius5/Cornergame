#include "entity.h"

Entity::Entity(int id, float x, float y, int w, int h, int drawWidth, int drawHeight) :
    id(id),
    x(x),
    y(y),
    width(w),
    height(h),
    drawWidth(drawWidth),
    drawHeight(drawHeight),
    actionState(IDLE),
    collision(NULL),
    score(NULL),
    physics(NULL),
    art(NULL),
    input(NULL),
    ai(NULL),
    health(NULL) {
}

Entity::~Entity() {
    if (this->collision)
        delete this->collision;
    if (this->score)
        delete this->score;
    if (this->physics)
        delete this->physics;
    if (this->art)
        delete this->art;
    if (this->input)
        delete this->input;
    if (this->ai)
        delete this->ai;
    if (this->health)
        delete this->health;
}

int Entity::getId() {
    return this->id;
}
