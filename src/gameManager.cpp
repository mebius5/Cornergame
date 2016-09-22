#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <cstdio>
#include <gameManager.h>

#define TWOPI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI

/* gameManager.cpp
 * Cornerstone <GAME NAME>
 */

double radToDeg(float radians) {
  return RAD_TO_DEG * radians;
}

int center(int large, int small) {
  return (large / 2 - small / 2);
}

SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH) {
  SDL_Rect rect = {
    center(largeW, smallW), center(largeH, smallH),
    smallW, smallH
  };
  return rect;
}

// Setup the instance of SDL2
void GameManager::setup() {
  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("Unable to initialize SDL:  %s\n", SDL_GetError());
    return;
  }

  // Initialize font
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return;
  }

  // Initialize image
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_img could not initialize! SDL_img Error: %s\n", IMG_GetError());
    return;
  }

  // Initialize Mixer
  if(Mix_Init(MIX_INIT_MOD)) {
    printf("The mixer failed to initialize!\n");
    return;
  }

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    printf("The mixer failed to initialize!\n");
    return;
  }

  // Initialize window
  window = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    SDL_WINDOW_SHOWN
  );

  if (!window) {
    printf("Unable to initialize window:  %s\n", SDL_GetError());
    return;
  }

  // Initialzie renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    printf("Unable to initialize renderer:  %s\n", SDL_GetError());
    return;
  }
}

// Load the necessary assets
void GameManager::load() {
  // Load music
  music = Mix_LoadMUS("abstract_tracking.xm");
  if (!music) {
    printf("Unable to load music:  %s\n", SDL_GetError());
  }

  // Load image
  SDL_Surface* loadedImage = IMG_Load("johns-hopkins-university-logo.png");
  SDL_Surface* finalImage = NULL;
  if (loadedImage == NULL) {
    printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
    return;
  } else {
    finalImage = SDL_ConvertSurface( loadedImage, loadedImage->format, 0 );
    if(finalImage == NULL) {
      printf( "Unable to optimize image! SDL Error: %s\n", SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedImage);
  }
  texWidth = finalImage->w;
  texHeight = finalImage->h;
  texture = SDL_CreateTextureFromSurface(renderer, finalImage);
  SDL_FreeSurface(finalImage);

  // Load fonts
  font = TTF_OpenFont("CaesarDressing-Regular.ttf", 30);
  font2 = TTF_OpenFont("CaesarDressing-Regular.ttf", 30);
}

// Cleanup the instance of SDL2
void GameManager::cleanup() {
  TTF_CloseFont(font);
  TTF_CloseFont(font2);
  SDL_DestroyTexture(texture);
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  //Set free pointers
  texture = NULL;
  music = NULL;
  renderer = NULL;
  window = NULL;
}

// updates rect positions and returns new direction
Cardinal northUpdate(SDL_Rect* text, SDL_Rect* shadow, int vShift, int minY) {
  if (text->y - vShift < minY) {
    text->y = minY;
    shadow->y = minY + SHADOW_SEP;
    return SOUTH;
  } else {
    text->y -= vShift;
    shadow->y -= vShift;
    return NORTH;
  }
}

Cardinal southUpdate(SDL_Rect* text, SDL_Rect* shadow, int vShift, int maxY) {
  if (text->y + vShift > maxY) {
    text->y = maxY;
    shadow->y = maxY + SHADOW_SEP;
    return NORTH;
  } else {
    text->y += vShift;
    shadow->y += vShift;
    return SOUTH;
  }
}

Cardinal eastUpdate(SDL_Rect* text, SDL_Rect* shadow, int hShift, int maxX) {
  if (text->x + hShift > maxX) {
    text->x = maxX;
    shadow->x = maxX + SHADOW_SEP;
    return WEST;
  } else {
    text->x += hShift;
    shadow->x += hShift;
    return EAST;
  }
}

Cardinal westUpdate(SDL_Rect* text, SDL_Rect* shadow, int hShift, int minX) {
  if (text->x - hShift < minX) {
    text->x = minX;
    shadow->x = minX + SHADOW_SEP;
    return EAST;
  } else {
    text->x -= hShift;
    shadow->x -= hShift;
    return WEST;
  }
}

// Calculate compound direction given two cardinal directions
Direction calcDir(Cardinal vertical, Cardinal horizontal) {
  if (vertical == NORTH) {
    if (horizontal == EAST)
      return NORTHEAST;
    else
      return NORTHWEST;
  } else {
    if (horizontal == EAST)
      return SOUTHEAST;
    else
      return SOUTHWEST;
  }
}

Direction swapDir(Direction original) {
  switch(original) {
  case NORTHEAST:
    return SOUTHWEST;
  case NORTHWEST:
    return SOUTHEAST;
  case SOUTHEAST:
    return NORTHWEST;
  default:
    return NORTHEAST;
  }
}

// Run the actual program
void GameManager::run() {
  bool running = true;
  float lastTime = 0;
  float time = 0;

  SDL_Color color={255, 255, 255, 255};
  SDL_Surface* textSurf = TTF_RenderUTF8_Blended(font, title, color);
  SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);

  SDL_Color shadowColor={0, 0, 0, 255};
  SDL_Surface* shadowSurf = TTF_RenderUTF8_Blended(font2, title, shadowColor);
  SDL_SetSurfaceAlphaMod(shadowSurf, 128);
  SDL_Texture* shadowTex = SDL_CreateTextureFromSurface(renderer, shadowSurf);

  SDL_Rect textureRect = centeredRect(width, height, texWidth, texHeight);

  SDL_Event event;
  Mix_PlayMusic(music, -1);
  Direction direction = SOUTHEAST;
  Cardinal vDirection = SOUTH;
  Cardinal hDirection = EAST;
  int minX = 0;
  int minY = textSurf->w/2;
  int maxX = width - textSurf->w - 10;       // accounts for rotation + shadow
  int maxY = height - textSurf->w/2 - 10;

  SDL_Rect textRect = {minX, minY, textSurf->w, textSurf->h};
  SDL_Rect shadowRect = {minX + 10, minY + 10, shadowSurf->w, shadowSurf->h};

  while (running) {
    int currentTime = SDL_GetTicks();
    int dt = currentTime - lastTime;
    time += dt/1000.0;
    lastTime = currentTime;

    if (time > twopi) {
      time -= twopi;
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE ||
            event.key.keysym.sym == SDLK_q) {
          running = false;
        } else if (event.key.keysym.sym == SDLK_SPACE) {
          direction = swapDir(direction);
        }
      }
    }

    // Update text location
    int hShift = dt/6;
    int vShift = dt/8;

    switch(direction) {
    case NORTHEAST:
      vDirection = northUpdate(&textRect, &shadowRect, vShift, minX);
      hDirection = eastUpdate(&textRect, &shadowRect, hShift, maxX);
      direction = calcDir(vDirection, hDirection);
      break;
    case NORTHWEST:
      vDirection = northUpdate(&textRect, &shadowRect, vShift, minX);
      hDirection = westUpdate(&textRect, &shadowRect, hShift, minX);
      direction = calcDir(vDirection, hDirection);
      break;
    case SOUTHEAST:
      vDirection = southUpdate(&textRect, &shadowRect, vShift, maxY);
      hDirection = eastUpdate(&textRect, &shadowRect, hShift, maxX);
      direction = calcDir(vDirection, hDirection);
      break;
    case SOUTHWEST:
      vDirection = southUpdate(&textRect, &shadowRect, vShift, maxY);
      hDirection = westUpdate(&textRect, &shadowRect, hShift, minX);
      direction = calcDir(vDirection, hDirection);
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, texture, NULL, &textureRect,
                     radToDeg(sin(time)), NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, shadowTex, NULL, &shadowRect,
                     radToDeg(time), NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, textTex, NULL, &textRect,
                     radToDeg(time), NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
  }
}

int main(void) {
  setup();
  load();
  run();
  cleanup();
}
