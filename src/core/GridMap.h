#ifndef CORE_GRID_MAP_H
#define CORE_GRID_MAP_H

#include <iostream>
#include <SDL2/SDL.h>

class GridMap { // TODO: implement from RenderClass or something
  public:
    GridMap();

    ~GridMap();

    void render(SDL_Renderer *renderer);
};

#endif
