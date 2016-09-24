
#include <SDL_render.h>
#include <SDL_image.h>
#include "entity.h"

Hero::Hero(SDL_Renderer * renderer, int startX, int startY, int width, int height) {
    this->location = new Location(startX, startY, width, height);

    // Load image
    SDL_Surface* loadedImage = IMG_Load("resources/hero.png");
    SDL_Surface* finalImage = NULL;
    if (loadedImage == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return;
    } else {
        finalImage = SDL_ConvertSurface(loadedImage, loadedImage->format, 0);
        if (finalImage == NULL) {
            printf("Unable to optimize image! SDL Error: %s\n", SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedImage);
    }

    /**
     * Free this later
     */
    //SDL_Rect rect = {100,200,50,50};

    //SDL_FillRect(finalImage, & rect, SDL_MapRGB(finalImage->format, 255, 0, 0));

    this->texture = new Texture(SDL_CreateTextureFromSurface(renderer, finalImage),1);
}

