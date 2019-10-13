//
// Created by Júlio César Lopes on 05/10/19.
//

#ifndef CGAME_TRANSFORMATIONS_H
#define CGAME_TRANSFORMATIONS_H

#include "../util/registry.h"

namespace System {
  void transformations(Registry &reg, float deltaTime, int windowWidth, int windowHeight);
  void transformations2D(Registry &reg, float deltaTime, int windowWidth, int windowHeight);
}


#endif //CGAME_TRANSFORMATIONS_H
