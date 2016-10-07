#include "aiComponent.h"
#include "artComponent.h"
#include "collisionComponent.h"
#include "inputComponent.h"
#include "physicsComponent.h"
#include "component.h"

std::vector<Command*>* Component::commandList = NULL;

Component::Component(Entity* entity) :
    valid(true),
    entity(entity) {
}

void Component::invalidate() {
    this->valid = false;
}

bool Component::isValid() {
    return this->valid;
}

void Component::setCommandList(std::vector<Command*>* commandListPtr) {
    Component::commandList = commandListPtr;
}

AiComponent::AiComponent(Entity* entity) :
    Component(entity) {
}

ArtComponent::ArtComponent(Entity* entity, int layer) :
    Component(entity),
    layer(layer) {
}

CollisionComponent::CollisionComponent(Entity* entity) :
    Component(entity) {
}

InputComponent::InputComponent(Entity* entity) :
    Component(entity) {
}

PhysicsComponent::PhysicsComponent() :
    Component(NULL) {
}
