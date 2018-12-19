#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "management/Render.h"

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

  // OpenGL Stuffs
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (glContext == NULL) {
    std::cout << "SDL_GL_CreateContext error: " << SDL_GetError() << std::endl;

    return 1;
  } else {
    // glew stuffs
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
      std::cout << "glewInit error: " << glewGetErrorString(glewError) << std::endl;
    
      return 1;      
    }
  }

  bool quit = false;
  SDL_Event e;

  RenderManagement renderManager = RenderManagement(renderer);

  while (!quit) {
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    renderManager.render();

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
