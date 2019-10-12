#ifndef CGAME_TERRAIN_H
#define CGAME_TERRAIN_H

#include <glm/ext.hpp>

#include "../util/registry.h"

void createSimpleTerrain(Registry &reg);
void makeTree(Registry &reg, glm::vec3 position);

#endif
