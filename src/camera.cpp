#include "camera.h"
#include "math.h"
#include <iostream>

Camera::Camera(SDL_Renderer * renderer, std::vector<ArtComponent*>& componentList, int windowW, int windowH) :
    renderer(renderer),
    componentList(componentList),
    levelW(-1),             // width and height of level (without copied portion)
    levelH(-1),
    previewOn(true),
    offsetX(0),             // offset for screen shake
    offsetY(0),
    shakeTime(0),
    maxShakeTime(1000),
    shakeDist(7),
    windowW(windowW),
    windowH(windowH),
    minX(0),                // current displayed window
    minY(0),
    maxX(windowW),
    maxY(windowH) {
}

Camera::~Camera() {
    this->renderer=NULL;
}

void Camera::startShake() {
    this->shakeTime = this->maxShakeTime;
}

void Camera::updateShake(int dt) {
    this->shakeTime -= dt;
    if (this->shakeTime > 0) {
        this->offsetX = cos(this->shakeTime) * this->shakeDist * (((float) this->shakeTime) / this->maxShakeTime);
        this->offsetY = sin(this->shakeTime) * this->shakeDist * (((float) this->shakeTime) / this->maxShakeTime);
    } else {
        this->offsetX = 0;
        this->offsetY = 0;
        this->shakeTime = 0;
    }
}

void Camera::draw(int dt, ArtComponent *artComponent) {
    Entity* entity = artComponent->entity;

    if(!previewOn && entity->collision && dynamic_cast<HeroCollisionComponent*>(entity->collision)) {
        detectBorderCollision(entity, dt);
        float xThresh = minX + windowW * .5;        // threshholds for camera shifting based on
        float yLowerThresh = minY + windowH * .75;  //  hero position
        float yUpperThresh = minY + windowH * .2;
        if (entity->y >= yLowerThresh) {            // shift y smoothly if past 3/4 of the way down
            shift(0, (entity->y - yLowerThresh) * .008 * dt);
        } else if (entity->y <= yUpperThresh) {
            shift(0, (entity->y - yUpperThresh) * .001 * dt);
        }
        if (entity->x >= (minX+(windowW)*.5)) {     // shift x smoothly if heroes past half way
            shift((entity->x - xThresh) * .00018 * dt, 0);
        }
    }

    if(artComponent->movesWithCamera){
        artComponent->entity->x = this->minX+artComponent->offsetX;
        artComponent->entity->y = this->minY+artComponent->offSetY;
    }

    if (entity->x + entity->width < minX || entity->y+entity->height < minY
            || entity->x > maxX || entity->y > maxY)
        return;

    SDL_Rect dest = { (int)entity->x - (int)minX + entity->width/2 - entity->drawWidth/2 - offsetX,
                      (int) entity->y - (int)minY + entity->height/2 - entity->drawHeight/2 - offsetY,
                      entity->drawWidth,
                      entity->drawHeight};

    SDL_RenderCopy(this->renderer, artComponent->getNextTexture(dt),
                   artComponent->getNextSrcRect(dt), &dest);
}

void Camera::shift(int dx, int dy) {
    minX += dx;
    minY += dy;
    maxX += dx;
    maxY += dy;

    if (!previewOn && minX >= levelW) {
        std::vector<ArtComponent*>::iterator it;
        for (it = this->componentList.begin(); it != this->componentList.end(); ) {
            if (!(*it)->isValid()) {        // remove invalid components
                *it = this->componentList.back();
                this->componentList.pop_back();
                continue;
            }

            if((*it)->entity->collision&& !dynamic_cast<TerrainCollisionComponent*>((*it)->entity->collision)){
                if((*it)->entity->x>= minX && (*it)->entity->x<=maxX){
                    (*it)->entity->x = (*it)->entity->x - levelW;
                }
            }
            ++it;
        }

        //TODO: Add command to respawn all enemy and heroes at updated location
        minX = minX - levelW;
        maxX = maxX - levelW;
    }
}

void Camera::resetCamera(int minX, int minY, int maxX, int maxY) {
    this->minX = minX;
    this->minY = minY;
    this->maxX = maxX;
    this->maxY = maxY;
}

void Camera::initializeCamera(int levelW, int levelH, bool previewOn) {
    this->levelW = levelW;
    this->levelH = levelH;
    this->previewOn = previewOn;
}

void Camera::detectBorderCollision(Entity *entity, int) {
    if (entity->collision) {
        if (entity->x < minX){
            this->borderBoundX(entity, minX+7);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        else if (entity->x + entity->width > maxX){
            this->borderBoundX(entity, maxX - entity->width-7);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        if (entity->y < minY){
            this->borderBoundY(entity, minY+7);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        else if (entity->y + entity->height > this->maxY){
            this->borderBoundY(entity, maxY - entity->height-7);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
    }
}

void Camera::borderBoundX(Entity* entity, float boundValue) {
    entity->x = boundValue;
    entity->physics->xVelocity = 0.0f;
    entity->collision->onBorderCollision();
}

void Camera::borderBoundY(Entity* entity, float boundValue) {
    entity->y = boundValue;
    entity->physics->yVelocity = 0.0f;
    entity->collision->onBorderCollision();
}
