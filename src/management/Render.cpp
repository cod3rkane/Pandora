#include "Render.h"

RenderManagement::RenderManagement(SDL_Renderer *renderer) {
  this->gridMap = GridMap();
  this->renderer = renderer;
};

RenderManagement::~RenderManagement() {

}

void RenderManagement::render() {
  this->gridMap.render(this->renderer);
}
