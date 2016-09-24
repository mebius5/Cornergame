//
// Created by Grady Xiao on 9/24/16.
//

#include <movementComponent.h>


MovementComponent::MovementComponent() {

}

MovementComponent::~MovementComponent() {

}

void MovementComponent::insertMovement(Command *command) {
    this->movementList.push_back(command);
}

/****
void MovementComponent::insertRandomMovement(Entity * entity){
    int random = rand() % 8;

    switch(random){
        case 0:
            insertMovement(new MoveUpCommand(entity));
        case 1:
            insertMovement(new MoveDownCommand(entity));
        case 2:
            insertMovement(new MoveLeftCommand(entity));
        case 3:
            insertMovement(new MoveRightCommand(entity));
        case 4:
            insertMovement(new MoveUpCommand(entity));
            insertMovement(new MoveLeftCommand(entity));
        case 5:
            insertMovement(new MoveUpCommand(entity));
            insertMovement(new MoveRightCommand(entity));
        case 6:
            insertMovement(new MoveDownCommand(entity));
            insertMovement(new MoveLeftCommand(entity));
        default:
            insertMovement(new MoveDownCommand(entity));
            insertMovement(new MoveRightCommand(entity));
    }
}
     ***/