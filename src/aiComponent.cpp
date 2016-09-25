#include "aiComponent.h"

AiComponent::AiComponent() {
    this->lastGenTime = 100.0f;
    this->lastGenCommand = NULL;
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
Command* AiComponent::generateBehavior(float time) {
    time = fmod(time, 4.0f);
    if (time < this->lastGenTime) {
        int random = rand() % this->commands.size();
        this->lastGenCommand = this->commands[random];
    }

    this->lastGenTime = time;
    return this->lastGenCommand;
}

// force the entity to pick a new behavior
void AiComponent::resetTimer() {
    this->lastGenTime = 100.0f;
}
