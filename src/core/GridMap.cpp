#include "GridMap.h"

GridMap::GridMap() {

}

GridMap::~GridMap() {

}

void GridMap::render(SDL_Renderer *renderer) {
  int const gridSize = 60;
  int x = 0;
  int y = 0;

  for (x = 0; x < 10; x++) {
    for (y = 0; y < 10; y++) {
      SDL_Rect rect = { x * gridSize, y * gridSize, gridSize, gridSize };
      SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderFillRect( renderer, &rect );
    }
  }
}
