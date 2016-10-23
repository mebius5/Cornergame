#include "aiComponent.h"
#include "artComponent.h"
#include "collisionComponent.h"
#include "inputComponent.h"
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

CollisionComponent::CollisionComponent(Entity* entity) :
    Component(entity) {
}

StaticCollisionComponent::StaticCollisionComponent(Entity* entity) :
    CollisionComponent(entity) {
    //xBinIndex(0),       //TODO: init this index and use it?
    //yBinIndex(0) {
}

DynamicCollisionComponent::DynamicCollisionComponent(Entity* entity) :
    CollisionComponent(entity),
    onGround(false),
    onLeftWall(false),
    onRightWall(false) {
}

InputComponent::InputComponent(Entity* entity) :
    Component(entity) {
}
