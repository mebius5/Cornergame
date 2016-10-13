#include "camera.h"
#include <iostream>


Camera::Camera(SDL_Renderer * renderer, int windowW, int windowH) :
renderer(renderer),
minX(0),
minY(0),
maxX(windowW),
maxY(windowH)
{

}

Camera::~Camera() {

}

void Camera::draw(int dt, ArtComponent * artComponent) {
    Entity* entity = artComponent->entity;
    SDL_Rect dest = { (int) entity->x - minX,
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