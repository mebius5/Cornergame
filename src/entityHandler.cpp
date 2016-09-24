#include "entityHandler.h"

EntityHandler::EntityHandler(SDL_Renderer* renderer) {
    this->nextId = 0;
    this->renderer = renderer;
}

Entity* EntityHandler::createHero(int x, int y) {
    SDL_Surface* loadedImage = IMG_Load("resources/hero.png");
    if (loadedImage == NULL) {
        std::cerr << "Unable to load image! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Surface* finalImage =
        SDL_ConvertSurface(loadedImage, loadedImage->format, 0);
    SDL_FreeSurface(loadedImage);
    if (finalImage == NULL) {
        std::cerr << "Unable to optimize image! SDL Error: "
                  << SDL_GetError() << std::endl;
        return NULL;
    }

    Entity* hero = new Entity(this->nextId++);
    hero->location = new LocationComponent(x, y, finalImage->w, finalImage->h);
    hero->art = new ArtComponent(SDL_CreateTextureFromSurface(this->renderer,
                                                              finalImage), 1);
    SDL_FreeSurface(finalImage);

    //Need to see parameter in future
    hero->input = new InputComponent();
    hero->input->insertKeyDown(SDLK_DOWN, new MoveDownCommand(hero));
    hero->input->insertKeyDown(SDLK_UP, new MoveUpCommand(hero));
    hero->input->insertKeyDown(SDLK_LEFT, new MoveLeftCommand(hero));
    hero->input->insertKeyDown(SDLK_RIGHT, new MoveRightCommand(hero));

    return hero;
}
