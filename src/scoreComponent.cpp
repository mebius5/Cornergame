#include "scoreComponent.h"

ScoreComponent::ScoreComponent(Entity* entity):
    Component(entity),
    wins(0) {
}

ScoreComponent::~ScoreComponent() {
    this->entity = NULL;
}
