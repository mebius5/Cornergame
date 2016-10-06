#include "scoreComponent.h"

#include <iostream>

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

int ScoreComponent::getScore() {
    return this->score;
}

void ScoreComponent::resetScore() {
    this->score = 0;
}

void ScoreComponent::setMultiplier(float multiplier) {
    this->multiplier = multiplier;
}