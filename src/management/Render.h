#ifndef MANAGEMENT_RENDER_H
#define MANAGEMENT_RENDER_H

#include <iostream>
#include "../core/GridMap.h"

class RenderManagement { // TODO: implement from RenderClass or something
  private:
    GridMap gridMap;
    SDL_Renderer *renderer;
  public:
    RenderManagement(SDL_Renderer *renderer);

    ~RenderManagement();

    void render();
};

#endif
