#include "camera.h"

Camera::Camera(SDL_Renderer * renderer, std::vector<ArtComponent*>& componentList, int windowW, int windowH) :
    renderer(renderer),
    componentList(componentList),
    minX(0),
    minY(0),
    maxX(windowW), 
    maxY(windowH),
    levelW(-1),
    levelH(-1)
{
}

Camera::~Camera() {
    this->renderer=NULL;
}

void Camera::draw(int dt, ArtComponent * artComponent) {
    Entity* entity = artComponent->entity;

    if(entity->collision && dynamic_cast<HeroCollisionComponent*>(entity->collision)) {
        if(levelW!=-1 && entity->x > levelW){
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
        detectBorderCollision(entity, dt);

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

void Camera::resetCamera(int windowW, int windowH) {
    minX=0;
    minY=0;
    maxX=windowW;
    maxY=windowH;
}

void Camera::setLevelWH(int levelW, int levelH) {
    this->levelW = levelW;
    this->levelH = levelH;
}

void Camera::detectBorderCollision(Entity *entity, int dt) {
    if (entity->collision) {
        if (entity->x < minX){
            this->borderBoundX(entity, minX+dt);
            entity->health->takeDamage(3);
        }
        else if (entity->x + entity->width > maxX){
            this->borderBoundX(entity, maxX - entity->width-dt);
            entity->health->takeDamage(3);
        }
        if (entity->y < minY){
            this->borderBoundY(entity, minY+dt);
            entity->health->takeDamage(3);
        }
        else if (entity->y + entity->height > this->maxY){
            this->borderBoundY(entity, maxY - entity->height-dt);
            entity->health->takeDamage(3);
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