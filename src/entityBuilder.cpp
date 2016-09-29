#include "entityBuilder.h"

EntityBuilder::EntityBuilder(SDL_Renderer* renderer) :
        nextId(0),
        renderer(renderer) {
}

Entity* EntityBuilder::createHero(int x, int y, const char* collisionSfxFile) {
    SDL_Surface* image = this->loadImage("resources/hero.png");
    Entity* hero = new Entity(this->nextId++, x, y, image->w, image->h);

    Mix_Chunk* chunk = Mix_LoadWAV(collisionSfxFile);
    if (!chunk) {
        std::cerr << "Unable to load chunk: " << Mix_GetError() << std::endl;
        return NULL;
    }

    hero->collision = new CollisionComponent(new PlaySoundCommand(chunk), NULL);
    hero->art = new StaticArtComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), 1);

    SDL_FreeSurface(image);

    //Need to see parameter in future
    hero->input = new InputComponent(.6f);
    hero->input->insertKeyDown(SDLK_DOWN, new MoveDownCommand(hero));
    hero->input->insertKeyDown(SDLK_UP, new MoveUpCommand(hero));
    hero->input->insertKeyDown(SDLK_LEFT, new MoveLeftCommand(hero));
    hero->input->insertKeyDown(SDLK_RIGHT, new MoveRightCommand(hero));

    return hero;
}

Entity* EntityBuilder::createEnemy(int x, int y) {
    SDL_Surface* image = this->loadImage("resources/enemy.png");
    Entity* enemy = new Entity(this->nextId++, x, y, 64, 64);

    enemy->collision = new CollisionComponent(NULL, new ResetAiCommand(enemy));
    enemy->art = new StaticArtComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), 1);

    SDL_FreeSurface(image);

    enemy->ai = new AiComponent(.2f);
    enemy->ai->newBehavior(new MoveDownCommand(enemy));
    enemy->ai->newBehavior(new MoveUpCommand(enemy));
    enemy->ai->newBehavior(new MoveLeftCommand(enemy));
    enemy->ai->newBehavior(new MoveRightCommand(enemy));

    return enemy;
}

// Surface must be freed when done!
SDL_Surface* EntityBuilder::loadImage(const char* filename) {
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
