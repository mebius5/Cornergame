#include "aiComponent.h"
#include "artComponent.h"
#include "collisionComponent.h"
#include "inputComponent.h"
#include "physicsComponent.h"

Component::Component(Entity* entity) :
    entity(entity) {
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
