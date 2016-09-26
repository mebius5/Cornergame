#include "aiComponent.h"

AiComponent::AiComponent(float speed) {
    this->lastGenTime = -600;
    this->lastGenCommand = NULL;
    this->speed = speed;
}

AiComponent::~AiComponent() {
    std::vector<Command *>::const_iterator it;
    for (it = this->commands.begin(); it != this->commands.end(); ++it){
        delete *it;
    }
    this->commands.clear();
}

void AiComponent::newBehavior(Command *command) {
    this->commands.push_back(command);
}

// picks a behavior at random, and keeps it until timer resets
Command* AiComponent::generateBehavior(int rawtime) {
    int timeDiff = rawtime - this->lastGenTime;
    if (timeDiff >= 600) {
        int random = rand() % this->commands.size();
        this->lastGenCommand = this->commands[random];
        this->lastGenTime = rawtime;
    }

    return this->lastGenCommand;
}

// force the entity to pick a new behavior
void AiComponent::resetTimer() {
    this->lastGenTime = 100.0f;
}
