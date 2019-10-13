//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_RENDER_H
#define CGAME_RENDER_H

#include "../util/registry.h"

namespace System {
    void shader(Registry &reg);
    void preRender(Registry &reg);
    void render(Registry &reg, float deltaTime, int windowWidth, int windowHeight);
    void cleanRender(Registry &reg);
}

#endif //CGAME_RENDER_H
