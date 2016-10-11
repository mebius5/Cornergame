#include "collisionComponent.h"

TerrainCollisionComponent::TerrainCollisionComponent(Entity *entity):
    CollisionComponent(entity)
{
}

void TerrainCollisionComponent::onEntityCollision(Entity *other) {
    //Calculate the sides of entity 1
    int leftA = this->entity->x;
    int rightA = this->entity->x + this->entity->width;
    int topA = this->entity->y;
    int bottomA = this->entity->y + this->entity->height;

    //Calculate the sides of entity 2
    int leftB = other->x;
    int rightB = other->x + other->width;
    int topB = other->y;
    int bottomB = other->y + other->height;

    if (bottomA >= topB && bottomB > bottomA){
        if(leftA <= leftB && rightA >= rightB){
            borderBoundY(other, bottomA);
        } else{
            if (rightA > leftB && rightA < rightB){
                if(rightA - leftB < bottomA-topB){
                    borderBoundX(other, rightA);
                } else{
                    borderBoundY(other, bottomA);
                }
            }
            else if (leftA < rightB && leftA > leftB){
                if(rightB - leftA < bottomA - topB){
                    borderBoundX(other, leftA-other->width);
                } else {
                    borderBoundY(other, bottomA);
                }
            }
        }
    }
    else if (topA <= bottomB && topB < topA){
        if(leftA <= leftB && rightA >= rightB){
            borderBoundY(other, topA-other->height);
        } else{
            if (rightA > leftB && rightA < rightB){
                if(rightA - leftB < bottomB-topA){
                    borderBoundX(other, rightA);
                } else{
                    borderBoundY(other, topA-other->height);
                }
            }
            else if (leftA < rightB && leftA > leftB){
                if(rightB - leftA < bottomB - topA){
                    borderBoundX(other, leftA-other->width);
                } else {
                    borderBoundY(other, topA-other->height);
                }
            }
        }
    }
    else if (rightA >= leftB && rightA < rightB){
        if(topA <= topB && bottomA >= bottomB){
            borderBoundX(other, rightA);
        } else {
            if (bottomA > topB && bottomB > bottomA){
                if(bottomA - topB < rightA - leftB){
                    borderBoundY(other, bottomA);
                } else{
                    borderBoundX(other, rightA);
                }
            } else if(topA < bottomB && topB < topA){
                if(bottomB - topA < rightA - leftB){
                    borderBoundY(other, topA-other->height);
                } else{
                    borderBoundX(other, rightA);
                }
            }
        }
    }
    else if (leftA <= rightB && leftA > leftB && topA <= topB && bottomA >= bottomB){
        if(topA <= topB && bottomA >= bottomB){
            borderBoundX(other, leftA-other->width);
        } else {
            if (bottomA > topB && bottomB > bottomA){
                if(bottomA - topB < rightB - leftA){
                    borderBoundY(other, bottomA);
                } else{
                    borderBoundX(other, leftA-other->width);
                }
            } else if(topA < bottomB && topB < topA){
                if(bottomB - topA < rightB - leftA){
                    borderBoundY(other, topA-other->height);
                } else{
                    borderBoundX(other, leftA-other->width);
                }
            }
        }
    }
}

void TerrainCollisionComponent::onBorderCollision() {
    
}

void TerrainCollisionComponent::borderBoundX(Entity* other, float boundValue) {
    other->x = boundValue;
    other->xVelocity = 0.0f;
    other->collision->onBorderCollision();
}

void TerrainCollisionComponent::borderBoundY(Entity* other, float boundValue) {
    other->y = boundValue;
    other->yVelocity = 0.0f;
    other->collision->onBorderCollision();
}