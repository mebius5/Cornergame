#ifndef CORNERGAME_ART_COMPONENT_H
#define CORNERGAME_ART_COMPONENT_H

#include <SDL_render.h>

class ArtComponent {
public:
    SDL_Texture* texture;
    int layer;

    ArtComponent(SDL_Texture* texture, int layer);
    ~ArtComponent();
};

#endif //CORNERGAME_ART_COMPONENT_H
