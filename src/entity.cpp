#include "entity.h"

Entity::Entity() {
    this->location = NULL;
    this->stats = NULL;
    this->physics = NULL;
    this->art = NULL;
    this->input = NULL;
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
}
