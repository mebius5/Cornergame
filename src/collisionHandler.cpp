#include <locationComponent.h>
#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::map<int, Entity *> & entityMap,
                                   std::list<Command *> & commandList, const int WIDTH, const int HEIGHT):
        entityMap(entityMap), commandList(commandList), width(WIDTH), height(HEIGHT){

}

void CollisionHandler::handleCollision(){
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        Entity * currentEntity = it ->second; //TODO: might have to free this
        if(currentEntity->input){ //Means that it's a player
            std::map<int, Entity*>::const_iterator b;
            for(b = entityMap.begin(); b != entityMap.end(); ++b){
                Entity * otherEntity = b -> second; //TODO: might have to free this
                if(currentEntity!=otherEntity && currentEntity->location && otherEntity->location){
                    //TODO: this also detects collision with another player, need fix later
                    if(isRectOverlapping(currentEntity->location, otherEntity->location)){
                        std::cout<<"Collision detected!"<<std::endl;
                        //TODO: Play audio effect for collision
                    }
                }
            }
        }
        handleBorderCollision(currentEntity);
    }
}

void CollisionHandler::handleBorderCollision(Entity *entity){ //TODO: might have to free entity
    if(entity->input){ //It's a hero
        if(entity->location->x<0){
            entity->location->x=0;
        }

        if (entity->location->x+entity->location->width >this->width){
            entity->location->x = this->width - entity->location->width;
        }

        if (entity->location->y<0){
            entity->location->y=0;
        }

        if (entity->location->y+entity->location->height > this->height){
            entity->location->y = this->height - entity->location->width;
        }

    } else if (entity->movement){ //It's an enemy
        if(entity->location->x<0){
            entity->location->x=0;
        }

        if (entity->location->x+entity->location->width >this->width){
            entity->location->x = this->width - entity->location->width;
        }

        if (entity->location->y<0){
            entity->location->y=0;
        }

        if (entity->location->y+entity->location->height > this->height){
            entity->location->y = this->height - entity->location->width;
        }

        std::list<Command *>::const_iterator iterator;
        for(iterator=entity->movement->movementList.begin();iterator!=entity->movement->movementList.end(); ++iterator){
            //Command * command = * iterator;
            //TODO: randomize movement
        }
    }
}

bool CollisionHandler::isRectOverlapping(LocationComponent * a, LocationComponent * b){
    //TODO: might have to free a & b

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->width;
    topA = a->y;
    bottomA = a->y + a->height;

    //Calculate the sides of rect b
    leftB = b->x;
    rightB = b->x + b->width;
    topB = b->y;
    bottomB = b->y + b->height;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}