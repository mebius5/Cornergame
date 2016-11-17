#include "camera.h"

Camera::Camera(SDL_Renderer* renderer, std::vector<Command*>& commandList,
               std::vector<ArtComponent*>& componentList,
               std::vector<BackgroundArtComponent*>& bgComponents,
               int windowW, int windowH) :
    renderer(renderer),
    commandList(commandList),
    componentList(componentList),
    bgComponents(bgComponents),
    loopLevelCommand(new LoopLevelCommand()),
    rumbleCommand(new PlaySoundCommand(SFX_RUMBLE)),
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
    delete this->loopLevelCommand;
}

void Camera::startShake() {
    this->shakeTime = this->maxShakeTime;
    this->commandList.push_back(this->rumbleCommand);
}

void Camera::updateShake(int dt) {
    this->shakeTime -= dt;
    if (this->shakeTime > 0) {
        this->offsetX = (int) (cos(this->shakeTime) * this->shakeDist * (((float) this->shakeTime) / this->maxShakeTime));
        this->offsetY = (int) (sin(this->shakeTime) * this->shakeDist * (((float) this->shakeTime) / this->maxShakeTime));
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
        float xThresh = (float) (minX + windowW * .5);        // threshholds for camera shifting based on
        float yLowerThresh = (float) (minY + windowH * .85);  //  hero position
        float yUpperThresh = (float) (minY + windowH * .15);
        if (entity->y >= yLowerThresh) {            // shift y smoothly if past 3/4 of the way down
            shift(0, (int) ((entity->y - yLowerThresh) * .05 * dt));
        } else if (entity->y <= yUpperThresh) {
            shift(0, (int) ((entity->y - yUpperThresh) * .01 * dt));
        }
        if (entity->x >= (minX+(windowW)*.5)) {     // shift x smoothly if heroes past half way
            shift((int) ((entity->x - xThresh) * .0007 * dt), 0);
        }
    }

    if(artComponent->movesWithCamera){
        artComponent->entity->x = this->minX+artComponent->offsetX;
        artComponent->entity->y = this->minY+artComponent->offsetY;
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

    std::vector<BackgroundArtComponent*>::iterator bgit;
    for (bgit = this->bgComponents.begin(); bgit != this->bgComponents.end(); ++bgit) {
        Entity* entity = (*bgit)->entity;
        entity->x = entity->x + dx * ((*bgit)->speed);
        entity->y = this->minY;
        //if ((*bgit)->entity->x + (*bgit)->entity->width <= minX) {
        //    (*bgit)->entity->x = (*bgit)->entity->x + (*bgit)->entity->width;
        //}
    }

    if (!previewOn && minX >= levelW) {     // perform level loop
        std::vector<ArtComponent*>::iterator it;
        for (it = this->componentList.begin(); it != this->componentList.end(); ) {
            if (!(*it)->isValid()) {        // remove invalid components
                *it = this->componentList.back();
                this->componentList.pop_back();
                continue;
            }

            Entity* entity = (*it)->entity;
            if (dynamic_cast<DynamicCollisionComponent*>(entity->collision)
                    && entity->x +  entity->width >= levelW) {
                entity->x = entity->x - levelW;
                if (RespawnEntity* reEnt = dynamic_cast<RespawnEntity*>(entity))
                    reEnt->shifted = true;
            }
            ++it;
        }

        minX = minX - levelW;
        maxX = maxX - levelW;
        this->commandList.push_back(this->loopLevelCommand);
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

void Camera::detectBorderCollision(Entity* entity, int dt) {
    int shiftAmount = (dt/2)+1;
    if (shiftAmount < 8)
        shiftAmount = 8;

    if (entity->x < minX) {
        if (minX - entity->x > 50)      // get squished!
            entity->health->die();
        entity->physics->bump(1);
        entity->health->takeDamage(10);
        entity->actionState = ACTION_DAMAGE;
    } else if (entity->x + entity->width > maxX) {
        entity->x = maxX - entity->width - shiftAmount;
        entity->physics->xVelocity = 0.0f;
    }
}
