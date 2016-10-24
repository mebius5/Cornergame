#include "camera.h"

Camera::Camera(SDL_Renderer * renderer, std::vector<ArtComponent*>& componentList, int windowW, int windowH) :
    renderer(renderer),
    componentList(componentList),
    levelW(-1),
    levelH(-1),
    previewOn(true),
    minX(0),
    minY(0),
    maxX(windowW),
    maxY(windowH)
{
}

Camera::~Camera() {
    this->renderer=NULL;
}

void Camera::draw(int dt, ArtComponent *artComponent) {
    Entity* entity = artComponent->entity;

    if(entity->collision && dynamic_cast<HeroCollisionComponent*>(entity->collision)) {
        if(!previewOn && levelW!=-1 && entity->x > levelW){
            if(levelW!=-1 && minX>=levelW){
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

                //TODO: Add command to respawn all enemy and heros at updated location
                minX = minX - levelW;
                maxX = maxX - levelW;
            }
        }
        if(!previewOn){
            detectBorderCollision(entity, dt);
        }
    }

    if(artComponent->movesWithCamera){
        artComponent->entity->x = this->minX+artComponent->offsetX;
        artComponent->entity->y = this->minY+artComponent->offSetY;
    }

    if(entity->x + entity->width < minX||
            entity->y+entity->height < minY||
            entity->x > maxX || entity->y > maxY)
        return;

    if(entity->collision && dynamic_cast<HeroCollisionComponent*>(entity->collision)){
        /***
        if(entity->x >= ((maxX+minX)/2)){
            shift(entity->x-(maxX+minX)/2,0);
        }***/
        if(entity->y >= (minY+(maxY-minY)*.75)){
            shift(0,entity->y-(minY+(maxY-minY)*.75));
        }
    }

    SDL_Rect dest = { (int)entity->x - minX,
                      (int) entity->y - minY,
                      entity->width,
                      entity->height};

    SDL_RenderCopy(this->renderer, artComponent->getNextTexture(dt),
                   artComponent->getNextSrcRect(dt), &dest);
}

void Camera::shift(int dx, int dy) {
    minX += dx;
    minY += dy;
    maxX += dx;
    maxY += dy;
    /****
if(levelW!=-1 && minX > levelW){
    minX = minX - levelW;
    maxX = maxX - levelW;
}

if(levelH!=-1 && minY > levelH){
    minY = minY - levelH;
    maxY = maxY - levelH;
}****/
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
        }
        else if (entity->x + entity->width > maxX){
            this->borderBoundX(entity, maxX - entity->width-7);
            entity->health->takeDamage(4);
        }
        if (entity->y < minY){
            this->borderBoundY(entity, minY+7);
            entity->health->takeDamage(4);
        }
        else if (entity->y + entity->height > this->maxY){
            this->borderBoundY(entity, maxY - entity->height-7);
            entity->health->takeDamage(4);
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