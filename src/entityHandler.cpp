#include "entityHandler.h"

EntityHandler::EntityHandler(SDL_Renderer* renderer) {
    this->nextId = 0;
    this->renderer = renderer;
}

Entity* EntityHandler::createHero(int x, int y) {
    Entity* hero = new Entity(this->nextId++);
    SDL_Surface* image = this->loadImage("resources/hero.png");
    hero->location = new LocationComponent(x, y, image->w, image->h);
    hero->art = new ArtComponent(SDL_CreateTextureFromSurface(this->renderer,
                                                              image), 1);
    SDL_FreeSurface(image);

    //Need to see parameter in future
    hero->input = new InputComponent();
    hero->input->insertKeyDown(SDLK_DOWN, new MoveDownCommand(hero));
    hero->input->insertKeyDown(SDLK_UP, new MoveUpCommand(hero));
    hero->input->insertKeyDown(SDLK_LEFT, new MoveLeftCommand(hero));
    hero->input->insertKeyDown(SDLK_RIGHT, new MoveRightCommand(hero));

    return hero;
}

Entity* EntityHandler::createEnemy(int x, int y) {
    Entity* enemy = new Entity(this->nextId++);
    SDL_Surface* image = this->loadImage("resources/enemy.png");
    enemy->location = new LocationComponent(x, y, image->w, image->h);
    enemy->art = new ArtComponent(SDL_CreateTextureFromSurface(this->renderer,
                                                              image), 1);
    SDL_FreeSurface(image);

    enemy->ai = new AiComponent();
    enemy->ai->newBehavior(new MoveDownCommand(enemy));
    enemy->ai->newBehavior(new MoveUpCommand(enemy));
    enemy->ai->newBehavior(new MoveLeftCommand(enemy));
    enemy->ai->newBehavior(new MoveRightCommand(enemy));

    return enemy;
}

SDL_Surface* EntityHandler::loadImage(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL) {
        std::cerr << "Unable to load image! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Surface* finalImage = SDL_ConvertSurface(image, image->format, 0);
    SDL_FreeSurface(image);
    if (finalImage == NULL) {
        std::cerr << "Unable to optimize image! SDL Error: "
                  << SDL_GetError() << std::endl;
        return NULL;
    }
    return finalImage;
}
