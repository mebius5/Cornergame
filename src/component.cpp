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

ArtComponent::ArtComponent(Entity* entity, int layer, bool movesWithCamera) :
    Component(entity),
    layer(layer),
    movesWithCamera(movesWithCamera){
    if(this->movesWithCamera){
        this->offsetX = entity->x;
        this->offSetY = entity->y;
    }
}

CollisionComponent::CollisionComponent(Entity* entity, bool staticObject) :
    Component(entity),
    staticObject(staticObject) {
}

InputComponent::InputComponent(Entity* entity) :
    Component(entity) {
}

PhysicsComponent::PhysicsComponent() :
    Component(NULL) {
}
