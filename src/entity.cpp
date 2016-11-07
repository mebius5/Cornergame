#include "entity.h"

Entity::Entity(int id, float x, float y, int w, int h, int drawWidth, int drawHeight) :
    id(id),
    x(x),
    y(y),
    initialX(x),
    initialY(y),
    width(w),
    height(h),
    drawWidth(drawWidth),
    drawHeight(drawHeight),
    actionState(IDLE),
    rotates(false),
    collision(NULL),
    score(NULL),
    physics(NULL),
    art(NULL),
    input(NULL),
    ai(NULL),
    health(NULL),
    powerUp(NULL),
    ammo(NULL) {
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
    if (this->powerUp)
        delete this->powerUp;
    if (this->ammo)
        delete this->ammo;
}

int Entity::getId() {
    return this->id;
}

void Entity::validate() {
    if (this->ai)
        this->ai->validate();
    if (this->art)
        this->art->validate();
    if (this->collision)
        this->collision->validate();
    if (this->input)
        this->input->validate();
    if (this->physics)
        this->physics->validate();
    if (this->health)
        this->health->validate();
    if (this->score)
        this->score->validate();
    if (this->powerUp)
        this->powerUp->validate();
    if (this->ammo)
        this->ammo->validate();
}

void Entity::invalidate() {
    if (this->ai)
        this->ai->invalidate();
    if (this->art)
        this->art->invalidate();
    if (this->collision)
        this->collision->invalidate();
    if (this->input)
        this->input->invalidate();
    if (this->physics)
        this->physics->invalidate();
    if (this->health)
        this->health->invalidate();
    if (this->score)
        this->score->invalidate();
    if (this->powerUp)
        this->powerUp->invalidate();
    if (this->ammo)
        this->ammo->invalidate();
}
