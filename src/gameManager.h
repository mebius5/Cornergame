#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <cstdio>

#define TWOPI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI

class GameManager {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Mix_Music* music;

  SDL_Texture* texture;
  int texWidth;
  int texHeight;
  TTF_Font* font;
  TTF_Font* font2;

  const char * title = "Intro to Video Games";
  const int width = 800;
  const int height = 600;

  //Methods
  void setup();
  void load();
  void run();
  void cleanup();

};
