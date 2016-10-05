#include "scoreComponent.h"

ScoreComponent::ScoreComponent(Entity * entity):
    Component(entity),
    score(0),
    multiplier(1) {
}

ScoreComponent::~ScoreComponent() {
    this->entity = NULL;
}

void ScoreComponent::addScore(int scoreIncrease) {
    this->score += int(this->multiplier * scoreIncrease);
}

void ScoreComponent::resetScore() {
    this->score = 0;
}

void ScoreComponent::setMultiplier(float multiplier) {
    this->multiplier = multiplier;
}
