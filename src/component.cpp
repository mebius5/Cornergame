#include "aiComponent.h"
#include "artComponent.h"
#include "collisionComponent.h"
#include "inputComponent.h"
#include "physicsComponent.h"
#include "statsComponent.h"

Component::Component(Entity* entity) :
    entity(entity) {
}

void Component::passCommand(Command* /*command*/) {

}

ArtComponent::ArtComponent(Entity* entity, int layer) :
    Component(entity),
    layer(layer) {
}

InputComponent::InputComponent(Entity* entity) :
    Component(entity) {
}

PhysicsComponent::PhysicsComponent() :
    Component(NULL) {
}

StatsComponent::StatsComponent() :
    Component(NULL) {
}

//TODO: move other 2 components here after creating abstract base classes!
