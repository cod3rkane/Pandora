#include <iostream>
#include <string>
#include <SDL2/SDL.h>

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

int initSDLFlag(Uint32 flag) {
  if (SDL_Init(flag) != 0) {
    std::cout << "SDL_INIT error: " << SDL_GetError() << std::endl;

    return 1;
  }

  return 0;
}

int main() {
  initSDLFlag(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pandora", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
