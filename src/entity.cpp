#include "entity.h"

Entity::Entity(int id) :
        id(id),
        location(NULL),
        stats(NULL),
        physics(NULL),
        art(NULL),
        input(NULL),
        ai(NULL) {
}

Entity::~Entity() {
    if (this->location)
        delete this->location;
    if (this->stats)
        delete this->stats;
    if (this->physics)
        delete this->physics;
    if (this->art)
        delete this->art;
    if (this->input)
        delete this->input;
    if (this->ai)
        delete this->ai;
}

int Entity::getId() {
    return this->id;
}
