#include "camera.h"

Camera::Camera(SDL_Renderer * renderer, int windowW, int windowH) :
renderer(renderer),
minX(0),
minY(0),
maxX(windowW),
maxY(windowH)
{

}

Camera::~Camera() {
    this->renderer=NULL;
}

void Camera::draw(int dt, ArtComponent * artComponent) {
    Entity* entity = artComponent->entity;


    if(entity->x + entity->width < minX||
            entity->y+entity->height < minY||
            entity->x > maxX || entity->y > maxY)
        return;

    if(entity->collision && dynamic_cast<HeroCollisionComponent*>(entity->collision)){
        if(entity->x >= ((maxX+minX)/2)){
            shift(entity->x-(maxX+minX)/2,0);
        }

        if(entity->y != (minY+(maxY-minY)*.75)){
            shift(0,entity->y-(minY+(maxY-minY)*.75));
        }
    }

    if(artComponent->movesWithCamera){
        artComponent->entity->x = this->minX+artComponent->offsetX;
        artComponent->entity->y = this->minY+artComponent->offSetY;
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
}

void Camera::resetCamera(int windowW, int windowH) {
    minX=0;
    minY=0;
    maxX=windowW;
    maxY=windowH;
}