#include "camera.h"

Camera::Camera(SDL_Renderer * renderer, std::vector<Command*>& commandList, std::vector<ArtComponent*>& componentList, int windowW, int windowH) :
    renderer(renderer),
    commandList(commandList),
    componentList(componentList),
    respawnPowerUpsCommand(new RespawnPowerUpsCommand()),
    levelW(-1),             // width and height of level (without copied portion)
    levelH(-1),
    previewOn(true),
    offsetX(0),             // offset for screen shake
    offsetY(0),
    shakeTime(0),
    maxShakeTime(1000),
    shakeDist(4),
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
        float yLowerThresh = minY + windowH * .85;  //  hero position
        float yUpperThresh = minY + windowH * .15;
        if (entity->y >= yLowerThresh) {            // shift y smoothly if past 3/4 of the way down
            shift(0, (entity->y - yLowerThresh) * .05 * dt);
        } else if (entity->y <= yUpperThresh) {
            shift(0, (entity->y - yUpperThresh) * .01 * dt);
        }
        if (entity->x >= (minX+(windowW)*.5)) {     // shift x smoothly if heroes past half way
            shift((entity->x - xThresh) * .0007 * dt, 0);
        }
    }

    if(artComponent->movesWithCamera){
        artComponent->entity->x = this->minX+artComponent->offsetX;
        artComponent->entity->y = this->minY+artComponent->offSetY;
    }

    if (entity->x + entity->width < minX || entity->y+entity->height < minY
            || entity->x > maxX || entity->y > maxY)
        return;

    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (entity->rotates && entity->physics->xVelocity != 0) {
        angle = atan((double)entity->physics->yVelocity/(double)entity->physics->xVelocity);
        angle *= 180/M_PI;
        if (entity->physics->xVelocity < 0) {
            flip = SDL_FLIP_HORIZONTAL;
        }
    }

    SDL_Rect dest = { (int)entity->x - (int)minX + entity->width/2 - entity->drawWidth/2 - offsetX,
                      (int) entity->y - (int)minY + entity->height/2 - entity->drawHeight/2 - offsetY,
                      entity->drawWidth,
                      entity->drawHeight};

    SDL_RenderCopyEx(this->renderer, artComponent->getNextTexture(dt),
                   artComponent->getNextSrcRect(dt), &dest, angle, NULL, flip);
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

        this->commandList.push_back(this->respawnPowerUpsCommand);
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

void Camera::detectBorderCollision(Entity *entity, int dt) {
    int shiftAmount = (dt/2)+1;
    if(shiftAmount< 8){
        shiftAmount = 8;
    }
    if (entity->collision) {
        if (entity->x < minX){
            this->borderBoundX(entity, minX+shiftAmount);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        else if (entity->x + entity->width > maxX){
            this->borderBoundX(entity, maxX - entity->width-shiftAmount);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        if (entity->y < minY){
            this->borderBoundY(entity, minY+shiftAmount);
            entity->health->takeDamage(4);
            entity->actionState = DAMAGE;
        }
        else if (entity->y + entity->height > this->maxY){
            this->borderBoundY(entity, maxY - entity->height-shiftAmount);
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
